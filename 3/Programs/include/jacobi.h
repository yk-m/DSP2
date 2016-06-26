#ifndef JACOBI_H
#define JACOBI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "matrix.h"
#include "eigen.h"

typedef struct {
	int i;
	int j;
	double value;
} Coordinate;

typedef struct {
	double sin;
	double cos;
} Trigonometry;

#include "jacobi.h"

Array_Eigen* jacobi( Matrix *m, double gap );
Array_Eigen* splitToEigen( Matrix *eigen_values, Matrix *eigen_vectors );
// void sort( Matrix *m );
void sort( Array_Eigen* eigens );
void rotate( Matrix *m, Coordinate position, Trigonometry angle );
void append( Matrix *m, Coordinate position, Trigonometry angle );
Trigonometry calcAngle( Matrix *m, Coordinate position );
Coordinate locateMaxValue( Matrix *m );
void repair( Matrix *matrix );

#endif