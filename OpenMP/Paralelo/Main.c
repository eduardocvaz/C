#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

int global=0;

int *AlocaMatriz(int m) //função para alocar a matriz dinamicamente
{
    int *M;
    M = (int *)malloc(sizeof(int *) * m);
    if (M == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    return M;
}

void embaralhar(int *vet, int vetSize)//função para embalhar elementos do vetor
{
    srand(11);
    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}
void imprimirmatriz(int *m, int n, char matriznome)//função para imprimir determinado vetor
{
    printf("Matriz %c[%i]\n", matriznome, n);
    for (int linha = 0; linha < n; linha++)
    {
        printf("%i\t", m[linha]);
    }
    printf("\n");
}

void swap(int *a, int *b)//função para trocar um elemento do vetor com o proximo
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *v, int n,int contador)//função que realizar as comparações e trocas e gerar as task
{   
    if (contador < 1)//caso o contador seja 0 a função termina, pois ja chegou na execução necessaria
        return;
    
    for (int i = 0; i < n; i++) //roda o vetor comparando um elemento com o outro, e caso esteja fora de posição ele troca
    {
        if (i==4 && n>0)//cada vez que chega na quarta posição do vetor ele abre uma task para que o proximo processo comece a rodar o vetor
        {   
            #pragma omp task//abrindo uma task com o contador--
            {
                bubbleSort(v, n,contador-1);
            }
        }
        
        if (v[i] > v[i + 1])
        {
            swap(&v[i], &v[i + 1]);
        }
    
    }
    global++;//Contando quantas vezes o bubble sort foi executado
    return;
}
void corretude(int *v, int n)//função para verificar se o vetor foi ordenado
{
    for (int i = 0; i < n; i++)
    {
        if (v[i] > v[i + 1])
        {
            printf("o vetor não esta ordenado.\n");
            return;
        }
    }
    printf("o vetor esta ordenado.\n");
    return;

}

int main(int argc, char const *argv[])
{
    struct timeval start, stop; //variaveis para guardar o tempo
    int numThreads = atoi(argv[1]);//recebe o numero de threads
    int n = atoi(argv[2]);//recebe o tamanho do problema

    int *a = AlocaMatriz(n);                 //alocando matriz a
    for (int linha = 0; linha <= n; linha++) //definindo valores aleatorios para cada posição das matrizes a e b
    {
        a[linha] = linha + 1;
    }
    //imprimirmatriz(a, n, 'a');//imprime vetor
    embaralhar(a, n);//desordena o vetor
    //imprimirmatriz(a, n, 'a');//imprime vetor
    gettimeofday(&start, 0); //começar a marcar o tempo
    #pragma omp parallel num_threads(numThreads) shared(a) shared(n) default(none)//abrindo região paralela 
    {
        int my_rank=omp_get_thread_num();
        //int num_threads=omp_get_num_threads();
        if (my_rank==0)//o processo 0 executa a função e os outros processos ficam esperando as task serem geradas
        {
            bubbleSort(a, n,n - 1); 
        }
    }
    

    gettimeofday(&stop, 0); //finaliza a contagem do tempo
    //imprimirmatriz(a, n, 'a');//imprime vetor
    corretude(a, n-1);//verifica se o vetor foi ordenado
    printf("o bubbleSort foi executado %i vezes\n",(n-1));//imprime quantas vezes o bubble sort foi executado

    FILE *fp;
    char outputFilename[] = "tempo_de_mm.txt";

    fp = fopen(outputFilename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp, "\t%f ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec)); //imprimindo tempo no arquivo tempo_de_mm.txt
    fclose(fp);
    free(a);
    return 0;
}