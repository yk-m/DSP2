#ifndef DSP_H
#define DSP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array.h"

#define PI 3.14159265358979

#define D_FN "../desired.txt"
#define E_FN "../error.txt"
#define E_LOG_FN "../error_log.txt"

Array_d* filter( Array_d* input, Array_d *filter );
double nthFilter( int n, Array_d* input, Array_d* filter );

Array_d* generateGaussSignal( int length );
double gauss( void );
void color( Array_d *noise, double coefficient );

double gain( int n, int length, Array_d *a );
double dot( int n, int length, Array_d *a, Array_d *b );
void initFilter( Array_d *filter );
Array_d* LMS( Array_d* input, Array_d* unknown_system );

#endif