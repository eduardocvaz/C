#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>
#include <time.h>

MPI_Status status;

double f(int n){ return pow(1.2, n);}

int main(int argc, char **argv)
{
    struct timeval start, stop;
    gettimeofday(&start, 0);
    int x_i;
    double a=1;
    double b=20;
    long double n=atof(argv[1]);
    long double h=(b-a)/n;
    //double area_inicial=((f(a)+f(b))*(b-a))/2;
    //printf("Area inicial=%f\n",area_inicial);

    int numtasks,taskid;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    double local_n=n/numtasks;
    double local_a=a+taskid*local_n*h;
    double local_b=local_a+local_n*h;
    //printf("local_a=%f\n",local_a);
    //printf("local_b=%f\n",local_b);
    //printf("local_n=%f\n\n",local_n);

    double local_area=(f(local_a)+f(local_b))/2;
    double area_total;
    for (int i = 1; i < local_n; i++)
    {
        //printf("area total1=%f\n",area_total);
        x_i=local_a+i*h;
        //printf("x_i=%i\n",x_i);
        local_area +=f(x_i);         
    }
    local_area =h*local_area;

if (taskid == 0) 
   {
        area_total = local_area;
        for (int proc=1; proc<numtasks; proc++) {
            MPI_Recv(&local_area,1,MPI_DOUBLE,proc,0,MPI_COMM_WORLD,&status);;
            area_total +=local_area;
            
        }
    printf("Area Total=%f",area_total);
   gettimeofday(&stop, 0);
   }
   else 
   {

      MPI_Send(&local_area,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
   }


if (taskid == 0) 
   {
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
   }

MPI_Finalize();
    return 0;
}
