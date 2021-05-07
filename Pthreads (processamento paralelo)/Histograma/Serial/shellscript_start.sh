#!/bin/bash

#SBATCH --partition=full
#SBATCH --job-name=decvaz
#SBATCH --output=decvazOutput.out
#SBATCH --error=decvazError.err
#SBATCH --time=0-00:40
#SBATCH --hint=compute_bound 

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32

#No Supercomputador, 1 nó = 32 Cores (ou CPUs)
#Lembrar que: TASK = PROCESSO

#A configuração acima reserva 1 nó inteiro (32 cpus no mesmo processador), vai rodar apenas 1 processo por vez,
# mas este processo terá acesso a 32 cores

#Loop principal de execuções. São 10 tentativas

	tentativas=10 #Quantas vezes o código será executado

	for cores in 1 #números de cores utilizados
	do
				for size in 500000000 #tamanho do problema
			do   	
				echo -e "\n$cores\t$size\t\t\c" >> "tempo_de_mm.txt" 

				for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
				do
					./teste $size
				done
                    #gnuplot -e "filename='graphics/image-$cores-$size'" "gnuplot"  
                    mv Histograma.txt histogram/"histograma-$cores-$size.txt" 
			done

	done
	
	exit 

