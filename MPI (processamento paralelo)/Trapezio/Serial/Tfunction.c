#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double f(int n){ return pow(1.2, n);}

int main(int argc, char const *argv[])
{
    struct timeval start, stop;
    gettimeofday(&start, 0);
    int x_i;
    double a=1;
    double b=20;
    long double n=atof(argv[1]);
    long double h=(b-a)/n;
    //printf("Area inicial=%f\n",area_inicial);
    //printf("Ponto a=%f\n",a);
    //printf("Ponto b=%f\n",b);

    //printf("F(a)=%f\n",f(a));
    //printf("F(b)=%f\n",f(b));
    //printf("n=%Lf\n",n);
    //printf("h=%1.15Lf\n",h);

    double area_total=(f(a)+f(b))/2;
    for (int i = 1; i < n; i++)
    {
        //printf("area total1=%f\n",area_total);
        x_i=a+i*h;
        //printf("x_i=%i\n",x_i);
        area_total +=f(x_i);
        
        
    }
    //printf("area total=%f\n",area_total);
    area_total =h*area_total;
    printf("area total=%f",area_total);
    //printf("area total=%f\n",area_total);
	gettimeofday(&stop, 0);

		FILE *fp;
		char outputFilename[] = "tempo_de_mm.txt";
	
		fp = fopen(outputFilename, "a");
		if (fp == NULL) {
			fprintf(stderr, "Can't open output file %s!\n", outputFilename);
			exit(1);
		}
	
		//testes de impressão no arquivo
		fprintf(fp, "\t%f ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
		//fprintf(fp, "\t%d ",numtasks); //número de tasks mpi
		//fprintf(fp, "\t%d ",N+1); //tamanho do problema+1

		fclose(fp);

    return 0;
}
