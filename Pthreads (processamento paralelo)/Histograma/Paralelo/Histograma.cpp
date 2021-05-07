// normal_distribution
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

long double nrolls;
long double vnumber;
int pnumber = 10;
long double divnumber;
int thread_count;
long double p[10] = {};//criando vetor

void *distribuir(void *rank);
int main(int argc, char const *argv[])
{
  struct timeval start, stop; //variaveis para guardar o temp  o
  gettimeofday(&start, 0);//Começa a marcar o tempo
  nrolls = atoi(argv[2]);//recebe numero de pontos
  vnumber = 1000000; //atoi(argv[2]);//tamanho total das unidades

  pnumber = 10;//tamanho do vetor
  divnumber = vnumber / pnumber;//dividindo total das unidades pelo vetor

  thread_count = strtol(argv[1], NULL, 10); //variavel que recebe o numero de threads

  long thread;
  pthread_t *thread_handles = new pthread_t[thread_count];

  //thread_handles = malloc(thread_count * sizeof(pthread_t));

  for (thread = 0; thread < thread_count; thread++) //iniciando a função distribuir para cada thread
  {
    pthread_create(&thread_handles[thread], NULL, distribuir, (void *)thread);
  }

  for (thread = 0; thread < thread_count; thread++) //esperando cada thread finalizar o processamento
  {
    pthread_join(thread_handles[thread], NULL);
  }

  gettimeofday(&stop, 0); //finaliza a contagem do tempo

  free(thread_handles);

  std::ofstream out("Histograma.txt");/*IMPRIMINDO RESULTADO PARA PLOTAR GRAFICO*/
  out << "# Histograma:" << std::endl;
  for (int i = 0; i < pnumber; ++i)
  {
    out << "[" << i << "-" << (i + 1) << "]:\t";
    out << p[i] << std::endl;
  }
  gettimeofday(&stop, 0); //finaliza a contagem do tempo
  std::ofstream out2;
  out2.open("tempo_de_mm.txt", std::ios::app);/*IMPRIMINDO TEMPO*/
  out2 << "\t" << (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
  return 0;
}
void *distribuir(void *rank)//Função executada pelas threads
{
  std::default_random_engine generator;
  std::normal_distribution<long double> distribution(0.0, (vnumber / 6));
  long my_rank = (long)rank;//variavel para indetificação de cada thread
  int local_rolls = nrolls / thread_count;//numero de pontos que cada thread deve criar
  int my_first = my_rank * local_rolls;//primeiro numero da cada thread
  int my_last = (my_rank + 1) * local_rolls - 1;//ultimo numero da cada thread
  for (int j=my_first; j <= my_last; ++j)//iniciando laça para gerar todos os pontos
  {
    double number = distribution(generator);//gerando os pontos

    for (int i = 0; i < pnumber; i++)//laço para verificar onde ficara cada ponto
    {
      if (number >= divnumber * (i) && number < divnumber * (i + 1))//adicionando os pontos ao vetor
      {
        ++p[i];
      }
    }
  }
  return NULL;
}