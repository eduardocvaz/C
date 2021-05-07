// normal_distribution
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sys/time.h>
#include <time.h>

long double nrolls;
long double vnumber;
int pnumber;
long double divnumber;

int main(int argc, char const *argv[])
{
  struct timeval start, stop; //variaveis para guardar o temp  o
  gettimeofday(&start, 0);    //Começa a marcar o tempo
  nrolls = atoi(argv[1]);     //recebe numero de pontos
  vnumber = 10000000;         //atoi(argv[2]);//tamanho total das unidades
  std::default_random_engine generator;
  std::normal_distribution<long double> distribution(0.0, (vnumber / 6));

  pnumber = 10;                  //tamanho do vetor
  divnumber = vnumber / pnumber; //dividindo total das unidades pelo vetor
  long double p[pnumber] = {};   //criando vetor

  for (int j = 0; j < nrolls; j++) //começando laço para gerar os pontos
  {

    double number = distribution(generator); //gerando numero

    for (int i = 0; i < pnumber; i++) //laço para saber o lugar a qual o ponto pertence
    {
      if (number >= divnumber * (i) && number < divnumber * (i + 1)) //verificando aonde o ponto deve ficar
      {                                                            
        ++p[i];
      }
    }
  }

  std::ofstream out("Histograma.txt"); /*IMPRIMINDO RESULTADO PARA PLOTAR GRAFICO*/
  out << "# Histograma:" << std::endl;
  for (int i = 0; i < pnumber; ++i)
  {
    out << "[" << i << "-" << (i + 1) << "]:\t";
    out << p[i] << std::endl;
  }
  gettimeofday(&stop, 0); //finaliza a contagem do tempo
  std::ofstream out2;
  out2.open("tempo_de_mm.txt", std::ios::app); /*IMPRIMINDO TEMPO*/
  out2 << "\t" << (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
  return 0;
}