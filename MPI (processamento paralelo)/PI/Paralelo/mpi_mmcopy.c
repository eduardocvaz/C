#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>
#include <time.h>

MPI_Status status;

#define SEED time(NULL)


int main(int argc, char **argv)
{

  	struct timeval start, stop;

	int n = atoi(argv[1]);
	gettimeofday(&start, 0);


int numtasks,taskid;
 srand( SEED );
 int i, count, mycount;
 double x,y,z;
 double pi=0;
 mycount = 0;


MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

 for(i = 0; i < (n/numtasks); ++i) 
 {

     x = (double)rand() / RAND_MAX;
     y = (double)rand() / RAND_MAX;
     z = x * x + y * y;
     if( z <= 1 ) mycount++;
 }
   if (taskid == 0) 
   {
      count = mycount;
      for (int proc=1; proc<numtasks; proc++) {
         MPI_Recv(&mycount,1,MPI_DOUBLE,proc,0,MPI_COMM_WORLD,&status);
         count +=mycount;

      }
   pi=(double)count/(n)*4;
   printf("PI=%f\n",pi);
   gettimeofday(&stop, 0);
   }
   else 
   {
      MPI_Send(&mycount,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
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
