#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int *Alocavetor(int m) //função para alocar a vetor dinamicamente
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

void embaralhar(int *vet, int vetSize) //função para embalhar elementos do vetor
{
    srand(13);
    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}
void imprimirvetor(int *m, int n, char vetornome) //função para imprimir determinado vetor
{
    printf("vetor %c[%i]\n", vetornome, n);
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

void bubbleSort(int *v, int n)//função que realizar as comparações e trocas 
{
    if (n < 1)//caso o n seja 0 a função termina, pois ja chegou na execução necessaria
        return;

    for (int i = 0; i < n; i++)//rodar o vetor comparando um elemento com o outro, e caso esteja fora de posição ele troca
        if (v[i] > v[i + 1])
            swap(&v[i], &v[i + 1]);
    bubbleSort(v, n - 1);//chama a função recursivamente 
}
int main(int argc, char const *argv[])
{
    struct timeval start, stop; //variaveis para guardar o tempo
    int n = atof(argv[1]);//recebe o tamanho do problema
    
    int *a = Alocavetor(n);                 //alocando vetor a
    for (int linha = 0; linha <= n; linha++) //definindo valores aleatorios para cada posição das vetores a e b
    {
        a[linha] = linha + 1;
    }
    //imprimirvetor(a, n, 'a');//imprime vetor
    embaralhar(a, n);//desordena o vetor
    //imprimirvetor(a, n, 'a');//imprime vetor
    gettimeofday(&start, 0); //começar a marcar o tempo
    bubbleSort(a, n - 1);//chamando a função passando o vetor e o tamanho
    //imprimirvetor(a, n, 'a');//imprime vetor
    gettimeofday(&stop, 0); //finaliza a contagem do tempo

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