#ifndef DCT_H
#define DCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "array.h"
#include "matrix.h"

Array_d* dct_1d( Array_d* vector );
Array_d* idct_1d( Array_d* vector );
Array_d* computeDCT_1d( Array_d* vector, bool inverse );

Matrix* dct_2d( Matrix* m );
Matrix* idct_2d( Matrix* m );
Matrix* computeDCT_2d( Matrix* m, bool inverse );

double generateDCTCoefficient( int dim, int n, int k );
Matrix* generateDCTMatrix( int size );

#endif