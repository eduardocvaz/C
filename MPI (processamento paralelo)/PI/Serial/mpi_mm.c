#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SEED time(NULL)
double montecarlo(double n) {
 srand( SEED );
 int i, count;
 double x,y,z,pi;
 count = 0;
 for(i = 0; i < n; ++i) 
 {
     x = (double)rand() / RAND_MAX;
     y = (double)rand() / RAND_MAX;
     z = x * x + y * y;
     if( z <= 1 ) count++;
 }

 pi = (double) count/n * 4;
 printf("PI=%f\n",pi);
 
 return(pi);
}

int main(int argc, char **argv)
{
  	struct timeval start, stop;

	gettimeofday(&start, 0);
	montecarlo(atof(argv[1]));
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
