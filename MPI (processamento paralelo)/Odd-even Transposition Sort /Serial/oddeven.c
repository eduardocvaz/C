#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void embaralhar(int *vet, int vetSize)
{
	for (int i = 0; i < vetSize; i++)
	{
		int r = rand() % vetSize;

		int temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}
}

void Odd_Even(int *vet, int n)
{
    int phase,i,temp;
    for (phase = 0; phase < n; phase++)
    {
        if (phase % 2 == 0)
        {
            for (i = 1; i < n; i+=2)
            {
                if (vet[i-1]>vet[i])
                {
                    temp=vet[i];
                    vet[i]=vet[i-1];
                    vet[i-1]=temp;
                }  
            }
            
        } 
        else
        {
            for (i = 1; i < n-1; i+=2)
            {
                if (vet[i]>vet[i+1])
                {
                    temp=vet[i];
                    vet[i]=vet[i+1];
                    vet[i+1]=temp;
                }
            }
        } 
    }
    
}

int main(int argc, char const *argv[])
{   
    //criando vetor aleatorio;
    int n=atof(argv[1]);
    int v[n];
     for (int i = 0; i < n; i++)
    {
        v[i]=i;
    }
    struct timeval start, stop;
    embaralhar(v,n);
    //========================
    gettimeofday(&start, 0);
    Odd_Even(v,n);
	gettimeofday(&stop, 0);

		FILE *fp;
		char outputFilename[] = "tempo_de_mm.txt";
	
		fp = fopen(outputFilename, "a");
		if (fp == NULL) {
			fprintf(stderr, "Can't open output file %s!\n", outputFilename);
			exit(1);
		}
		fprintf(fp, "\t%f ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
		fclose(fp);

    
    return 0;
}
