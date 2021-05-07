#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

void matrizmult(int **a, int **b, int **v, int n)//função para multiplicar duas matrizes e colocar em outra
{

    for (int linha = 0; linha < n; linha++)
    {
        for (int coluna = 0; coluna < n; coluna++)
        {
            v[linha][coluna] = a[linha][coluna] * b[linha][coluna];
        }
    }
}
void imprimirmatriz(int **m, int n, char matriznome) //função para imprimir determinada matriz
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
int main(int argc, char const *argv[])
{
    struct timeval start, stop;//variaveis para guardar o tempo

    gettimeofday(&start, 0);//começar a marcar o tempo
    
    srand(13);
    double n = atof(argv[1]);

    int **a = AlocaMatriz(n, n);//alocando matriz a
    int **b = AlocaMatriz(n, n);//alocando matriz b
    int **v = AlocaMatriz(n, n);//alocando matriz v

    for (int linha = 0; linha < n; linha++) //definindo valores aleatorios para cada posição das matrizes a e b
    {

        for (int coluna = 0; coluna < n; coluna++)
        {
            a[linha][coluna] = rand() % 1000;
            b[linha][coluna] = rand() % 1000;
        }
    }

    
    matrizmult(a, b, v, n);//multiplica as matrizes
    //imprimirmatriz(a,n,'a');
    //imprimirmatriz(b,n,'b');
    //imprimirmatriz(v,n,'v');

    gettimeofday(&stop, 0);//finaliza a contagem do tempo

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
