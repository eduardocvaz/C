#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#include <time.h>

MPI_Status status;

void embaralhar(int *vet, int vetSize)//função para embaralhar o vetor
{
    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}

void Odd_Even(int *vet, int n)//função para organizar o vetor
{
    int phase, i, temp;
    for (phase = 0; phase < n; phase++)
    {
        if (phase % 2 == 0)
        {
            for (i = 1; i < n; i += 2)
            {
                if (vet[i - 1] > vet[i])
                {
                    temp = vet[i];
                    vet[i] = vet[i - 1];
                    vet[i - 1] = temp;
                }
            }
        }
        else
        {
            for (i = 1; i < n - 1; i += 2)
            {
                if (vet[i] > vet[i + 1])
                {
                    temp = vet[i];
                    vet[i] = vet[i + 1];
                    vet[i + 1] = temp;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    //criando vetor aleatorio;
    int size = atof(argv[1]);
    int *v = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)//criando vetor
    {
        v[i] = i;
    }
    struct timeval start, stop;
    embaralhar(v, size);//embaralhando vetor

    int numtasks, taskid;

    gettimeofday(&start, 0);//inicio da contagem de tempo
    //=======================================Inicio=======================================

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    int local_size = size / numtasks;
    int *local_v = malloc(sizeof(int) * local_size);


    if (taskid == 0)//==========Destribuindo o vetor entre os processos============
    {
        MPI_Scatter(v, local_size, MPI_INT, local_v, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(v, local_size, MPI_INT, local_v, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }//========================================================

    Odd_Even(local_v, local_size);//Cada processo ordena seu proprio vetor usando a função

    int *local_temp = malloc(sizeof(int) * (local_size * 2));//vetor temporario para guardar a junção 
    for (int phase = 0; phase < numtasks - 1; phase++)//começando a odd even so que dessa vez usando os processos
    {
        if (phase % 2 == 0)//fase par
        {
            if (taskid % 2 == 0)
            {

                for (int i = 0; i < local_size; i++)
                {
                    local_temp[i] = local_v[i];//guardando o vetor do primeiro processo
                }
                MPI_Recv(local_v, local_size, MPI_INT, (taskid + 1), 0, MPI_COMM_WORLD, &status);//recebendo novo vetor
                for (int i = 0; i < local_size; i++)
                {
                    local_temp[i + local_size] = local_v[i];//guardando vetor do segundo processo
                }
                Odd_Even(local_temp, local_size * 2);//organizando os dois vetores
                for (int i = 0; i < local_size; i++)
                {
                    local_v[i] = local_temp[i + local_size];//organizando para devolver a segunda parte do vetor para o segundo processo
                }
                MPI_Send(local_v, local_size, MPI_INT, (taskid + 1), 0, MPI_COMM_WORLD);//enviando vetor
                for (int i = 0; i < local_size; i++)
                {
                    local_v[i] = local_temp[i];//devolvendo primeiro vetor para o primeiro processo 
                }
            }
            else
            {
                MPI_Send(local_v, local_size, MPI_INT, (taskid - 1), 0, MPI_COMM_WORLD);//segundo processo enviando vetor
                MPI_Recv(local_v, local_size, MPI_INT, (taskid - 1), 0, MPI_COMM_WORLD, &status);//segundo processo recebendo vetor
            }
        }
        if (phase % 2 == 1)//fase impar
        {
            if (taskid % 2 == 1 && taskid != numtasks - 1)
            {

                for (int i = 0; i < local_size; i++)
                {
                    local_temp[i] = local_v[i];//guardando o vetor do primeiro processo
                }
                MPI_Recv(local_v, local_size, MPI_INT, (taskid + 1), 0, MPI_COMM_WORLD, &status);//recebendo novo vetor
                for (int i = 0; i < local_size; i++)
                {
                    local_temp[i + local_size] = local_v[i];//guardando vetor do segundo processo
                }
                Odd_Even(local_temp, local_size * 2);//organizando os dois vetores
                for (int i = 0; i < local_size; i++)
                {
                    local_v[i] = local_temp[i + local_size];//organizando para devolver a segunda parte do vetor para o segundo processo
                }
                MPI_Send(local_v, local_size, MPI_INT, (taskid + 1), 0, MPI_COMM_WORLD);//enviando vetor
                for (int i = 0; i < local_size; i++)
                {
                    local_v[i] = local_temp[i];//devolvendo primeiro vetor para o primeiro processo 
                }
            }
            else if (taskid % 2 == 0 && taskid != 0)
            {
                MPI_Send(local_v, local_size, MPI_INT, (taskid - 1), 0, MPI_COMM_WORLD);//segundo processo enviando vetor
                MPI_Recv(local_v, local_size, MPI_INT, (taskid - 1), 0, MPI_COMM_WORLD, &status);//segundo processo recebendo vetor
            }
        }
    }
    
    MPI_Gather(local_v, local_size, MPI_INT, v, local_size, MPI_INT, 0, MPI_COMM_WORLD);//juntando todos os vetores organizados no vetor principal e completo

    MPI_Finalize();
    //===============================================Fim===================================================
    gettimeofday(&stop, 0);//fim da contagem de tempo
    free(local_v);//desalocando vetor
    free(local_temp);//desalocando vetor

    if (taskid == 0)//primeiro processo escreve o tempo de execução no arquivo
    {
        FILE *fp;
        char outputFilename[] = "tempo_de_mm.txt";

        fp = fopen(outputFilename, "a");
        if (fp == NULL)
        {
            fprintf(stderr, "Can't open output file %s!\n", outputFilename);
            exit(1);
        }

        //impressão no arquivo
        fprintf(fp, "\t%f ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));


        fclose(fp);
    }
    
    return 0;
}
