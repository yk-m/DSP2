#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "iof.h"
#include "error.h"

typedef struct {
	double **a;
	int row;
	int column;
} Matrix;

Matrix* newMatrix( int row, int column );
Matrix* newIdentityMatrix( int row, int column );
void freeMatrix( Matrix* d );

Matrix *loadFileAsMatrix( const char file[], bool ask_filename );
void determineDimensionOfMatrix( const char file_name[], int* row, int* column );
int countSplitter( const char* string, const char splitter );

void printMatrix( Matrix* a );
void printMatrixToFile( Matrix* a, const char file_name[] );

Matrix *subtract( Matrix *a, Matrix *b );
Matrix *multiply( Matrix *a, Matrix *b );
Matrix *multiplyByScalar( Matrix *a, double b );
Matrix *divideByScalar( Matrix *a, double b );
Matrix *transpose( Matrix* m );
double dotProduct( Matrix* a, Matrix* b );
double calcNorm( Matrix* a );

void MatrixLoadError();
void InvalidMatrixFormatError();

#endif