//
// Main.c
// Practica4
//
/*
---> Creodo por Chiripiorcas
---> Conformado por:
		-> Benjamin Hoyos Herrera
		-> Angel Yedid Nacif Mena
		-> Genaro Gonzalez Lozada
		-> Carlos Abraham Martinez Zamora
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParallelMatrix.h"

int main(int argc, char** argv)
{
	srand(time(NULL));
	
	//Variables a utilizar
	int i,j,ren,col;
	int *a_mat=NULL;
	int *b_mat=NULL;
	int numProcs,maxThreads,numThreads;

	double normal,parall;
	numProcs = omp_get_num_procs();
	maxThreads = omp_get_max_threads();

	//Instruccion para imprimir la cantidad de nucleos disponibles en la computadora
	printf("Numero de procesadores disp. ->\t %d\nNumero de hilos en paralelo disp. ->\t%d\n\n",numProcs,maxThreads);



	//Instrucciones para realizar la simulacion con 1, 2, 3 y 4 hilos disponibles para 4 nucleos.
	//Instrucciones para utilizar una cantidad de hilos.
	for (i=1;i<5;i++){

		//y la cantidad maxima de hilos que se solicitaron.
		printf("\n\n==============Thread Num. %d=====================\n",i);
		/*Instrucciones para realizar la simulacion con matrices de
		10 x 20
		50 x 50
		200 x 100
		1000 x 1000
		1200 x 1200
		1920 x 1080.
		*/
		for(j=0;j<6;j++){
			switch (j)
			{
				case 0:
					printf("caso 0\n");
					ren = 10;
					col = 20;
					break;
				case 1:
					printf("caso 1\n");
					ren = 50;
					col = 50;
					break;
				case 2:
					printf("caso 2\n");
					ren = 100;
					col = 200;
					break;
				case 3:
					printf("caso 3\n");
					ren = 1000;
					col = 1000;
					break;
				case 4:
					printf("caso 4\n");
					ren = 1200;
					col = 1200;
					break;
				case 5:
					printf("caso 5\n");
					ren = 1920;
					col = 1080;
					break;
			}
			//Funcion para inicializar las matrices.
			a_mat = (int*)malloc(ren*col*sizeof(int));
			llenado_recorr_mat(a_mat,ren,col);

			b_mat = (int*)malloc(ren*col*sizeof(int));
			llenado_recorr_mat(b_mat,ren,col);

			//Funcion para sumar las matrices de forma no paralela y toma de tiempo.
			normal = suma_n(a_mat,b_mat,ren,col);
			//Funcion para sumar las matrices de forma paralela y toma de tiempo.
			parall = suma_p(a_mat,b_mat,ren,col,i);
			printf("\tTiempo normal Suma: %lf Tiempo parall Suma: %lf\n",normal,parall);

			//Funcion para obtener el valor maximo de forma no paralela y toma de tiempo.
			normal = max_valor_n(a_mat,ren,col);
			//Funcion para obtener el valor maximo de forma paralela y toma de tiempo.
			parall = max_valor_p(a_mat,ren,col,i);
			printf("\tTiempo normal Val. Max: %lf Tiempo parall Val Max: %lf\n",normal,parall);

			//Impresion de tabla de tiempos de TODA la simulacion.
		}
		
	}

	return EXIT_SUCCESS;
}
