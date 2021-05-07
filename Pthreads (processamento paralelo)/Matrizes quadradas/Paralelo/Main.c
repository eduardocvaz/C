#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


int thread_count;

int **AlocaMatriz(int m, int n) //função para alocar a matriz dinamicamente
{
    int **M;
    int i;
    M = (int **)malloc(sizeof(int *) * m);
    if (M == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    for (i = 0; i < m; i++)
    {
        M[i] = (int *)malloc(sizeof(int) * n);
        if (M[i] == NULL)
        {
            printf("Memoria insuficiente.\n");
            exit(1);
        }
    }
    return M;
}
void LiberaMatriz(int **M, int m)//função para liberar a matriz
{
    int i;
    for (i = 0; i < m; i++)
        free(M[i]);
    free(M);
}

void imprimirmatriz(int **m, int n, char matriznome)//função para imprimir determinada matriz
{
    printf("Matriz %c[%i][%i]\n", matriznome, n, n);
    for (int linha = 0; linha < n; linha++)
    {
        for (int coluna = 0; coluna < n; coluna++)
        {
            printf("%i\t", m[linha][coluna]);
        }
        printf("\n");
    }
}
//variaveis globais
static double n;
int **a;
int **b;
int **v;

void *matrizmult(void *rank)//função para  multiplicar as matrizes usando pthread
{
    long my_rank = (long)rank;
    int local_n = n / thread_count;
    int my_first = my_rank * local_n;
    int my_last = (my_rank + 1) * local_n - 1;

    for (int linha = my_first; linha <= my_last; linha++)
    {
        for (int coluna = 0; coluna < n; coluna++)
        {
            v[linha][coluna] = a[linha][coluna] * b[linha][coluna];
        }
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    struct timeval start, stop;//variaveis para guardar o temp  o
    gettimeofday(&start, 0);
    srand(13);

    n = atoi(argv[2]);

    a = AlocaMatriz(n, n);//alocando matriz a
    b = AlocaMatriz(n, n);//alocando matriz b
    v = AlocaMatriz(n, n);//alocando matriz v

    for (int linha = 0; linha < n; linha++)//definindo valores aleatorios para cada posição das matrizes a e b
    {

        for (int coluna = 0; coluna < n; coluna++)
        {
            a[linha][coluna] = rand() % 1000;
            b[linha][coluna] = rand() % 1000;
        }
    }


    long thread;
    pthread_t *thread_handles;

    thread_count = strtol(argv[1], NULL, 10);//variavel que recebe o numero de threads
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++)//iniciando a função matrizmult para cada thread
    {
        pthread_create(&thread_handles[thread], NULL, matrizmult, (void *)thread);
    }

    for (thread = 0; thread < thread_count; thread++)//esperando cada thread finalizar o processamento 
    {
        pthread_join(thread_handles[thread], NULL);
    }

    gettimeofday(&stop, 0);//finaliza a contagem do tempo

    free(thread_handles);

    //imprimirmatriz(a, n, 'a');
    //imprimirmatriz(b, n, 'b');
    //imprimirmatriz(v, n, 'v');

    LiberaMatriz(a, n);//libera a matriz a
    LiberaMatriz(b, n);//libera a matriz b
    LiberaMatriz(v, n);//libera a matriz v

    FILE *fp;
    char outputFilename[] = "tempo_de_mm.txt";

    fp = fopen(outputFilename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp, "\t%f ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));//imprimindo tempo no arquivo tempo_de_mm.txt
    fclose(fp);

    return 0;
}
