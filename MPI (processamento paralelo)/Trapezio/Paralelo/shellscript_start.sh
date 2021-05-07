#!/bin/bash

#INFORMAÇÕES- Para rodar no computador pessoal.
# EXECUTAR NO TERMINAL: ./shellscript_start.sh
	#Caso não funcione, conceda permissão máxima ao este arquivo: chmod 777 shellscript_start.sh

#OPCIONAL: apagar arquivos temporários (gerados ou não pelo .c).
rm tempo_de_mm.txt
rm tfunction

#Compilação de Código. Modifique para o que mais se adequa a você.
mpicc -g -Wall Tfunction.c -o tfunction -lm

#OBRIGATÓRIO: Laço de iteração para resgate dos tempos de acordo com "cores" e "size"

#Loop principal de execuções. São 10 tentativas
	tentativas=5 #Quantas vezes o código será executado dado um par (cores,size)

	for cores in 1 2 3 4 8 #números de cores utilizados
	do
			for size in 800000000 1000000000 1100000000 1150000000 #tamanho do problema
			do   	
				echo -e "\n$cores\t$size\t\t\c" >> "tempo_de_mm.txt" 

				for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
				do
					#Executar o código. Modifique para o que mais se adequa a você.
                    mpirun -np  $cores  ./tfunction $size
					#mpirun ./mpi_mm 
					#no meu PC, tive que utilizar "--oversubscrive" para rodar. No seu pode não ser necessário. 
				done
			done

	done
	
	exit 




exit
