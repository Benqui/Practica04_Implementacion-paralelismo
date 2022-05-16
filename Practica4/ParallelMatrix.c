//
// ParallelMatrix.c
// Practica4
//
//

#include "ParallelMatrix.h"

//Definicion de funciones
void llenado_recorr_mat(int* mat,int ren,int col){
    int r,c;
    //llenado de la mat
    for(r = 0; r < ren; r++)
	{
		for(c = 0; c < col; c++)
		{
			*(mat + r * col + c) = rand()%255;
		}
	}

    // printf("MatrizA:\n");
	// for(r = 0; r < ren; r++)
	// {
	// 	for(c = 0; c < col; c++)
	// 	{
	// 		printf("%d\t",*(mat + r * col + c));
	// 	}
	// 	printf("\n");
	// }
}

double suma_n(int*a_mat,int*b_mat,int ren,int col){

    struct timespec t0, t1;
	double tiempoMedido;

    int r,c,*r_mat=NULL;

    if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}

    r_mat=(int*)malloc(ren*col*sizeof(int));
    for(r = 0; r < ren; r++)
	{
		for(c = 0; c < col; c++)
		{
			*(r_mat + r * col + c) = *(a_mat + r * col + c)+*(b_mat + r * col + c);
		}
	}
    if(clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
    tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
    return tiempoMedido;
    // printf("Matriz Res:\n");
	// for(r = 0; r < ren; r++)
	// {
	// 	for(c = 0; c < col; c++)
	// 	{
	// 		printf("%d\t",*(r_mat + r * col + c));
	// 	}
	// 	printf("\n");
	// }
}

double max_valor_n(int* mat,int ren ,int col){
    int r,c,max=0;
    struct timespec t0, t1;
	double tiempoMedido;
    if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}

	for(r = 0; r < ren; r++)
	{
		for(c = 0; c < col; c++)
		{
			if(*(mat + r * col + c)>max) max = *(mat + r * col + c);
		}
        //printf("\n"); <--- por este maldito printf me la pase 45 minutos viendo por que no me salia bien la tabla de resultados de tiempo quiero llorar ama me dio amsieda --Bhh
	}
	//printf("El numero maximo es el %d\n",max);
     if(clock_gettime(CLOCK_REALTIME,&t1) != 0)
	 {
	 	printf("Error al llamar clock_gettime para t1\n");
	 	exit(EXIT_FAILURE);
	}

    tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
    return tiempoMedido;
}

double suma_p(int*a_mat,int*b_mat,int ren,int col,int threads){
    struct timespec t0, t1;
	double tiempoMedido;

    int r,c,*r_mat=NULL;
    r_mat=(int*)malloc(ren*col*sizeof(int));
    omp_set_num_threads(threads);
    if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
    #pragma omp parallel for private(c)
    for(r = 0; r < ren; r++)
	{
		for(c = 0; c < col; c++)
		{
			*(r_mat + r * col + c) = *(a_mat + r * col + c)+ *(b_mat + r * col + c);
		}
	}
    if(clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
    tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
    return tiempoMedido;
}

double max_valor_p(int*mat,int ren,int col,int threads){
    struct timespec t0, t1;
	double tiempoMedido;

    int r,c,max=0;
    omp_set_num_threads(threads);
    if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
    #pragma omp parallel for private(c)
    for(r = 0; r < ren; r++)
	{
		for(c = 0; c < col; c++)
		{
            // printf("Hilos %d\n",omp_get_num_threads());
			if(*(mat + r * col + c)>max) max = *(mat + r * col + c);
		}
        //printf("\n"); <--- por este maldito printf me la pase 45 minutos viendo por que no me salia bien la tabla de resultados de tiempo quiero llorar ama me dio amsieda --Bhh
	}
    if(clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
    tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
    return tiempoMedido;
}
