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

#endif