#ifndef EIGEN_H
#define EIGEN_H

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "matrix.h"

typedef struct {
	double value;
	Matrix* vector;
} Eigen;

typedef struct {
	Eigen **a;
	int length;
} Array_Eigen;


Eigen* newEigen();
void freeEigen( Eigen* e );
void printEigen( Eigen* e );

Array_Eigen* newArray_Eigen( int length );
void freeArray_Eigen( Array_Eigen* e );
void printArray_Eigen( Array_Eigen* e );

#endif