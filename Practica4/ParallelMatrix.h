//
// ParallelMatrix.h
// Practica4
//
//

#pragma once

#ifndef ParallelMatrix_h
#define ParallelMatrix_h

#include <unistd.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Prototipos de funciones
void llenado_recorr_mat(int*,int,int);
double suma_n(int*,int*,int,int);
double suma_p(int*,int*,int,int,int);

double max_valor_n(int*,int,int);
double max_valor_p(int*,int,int,int);




#endif
