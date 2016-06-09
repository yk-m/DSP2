#ifndef CORRELATION_H
#define CORRELATION_H

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "array.h"
#include "array_c.h"
#include "fft.h"

Array_d* calcAutoCorrelationFunction( Array_d* original_vector );
Array_d* calcCorrelationFunction( Array_d* original_vector1, Array_d *original_vector2 );
Array_c* power_old( Array_c* vec );
Array_c* power( Array_c* vec1, Array_c* vec2 );
Array_c* expand( Array_c* original_vector );
int calcDimForFFT( int original_dim );

#endif