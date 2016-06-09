#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	double re;
	double im;
} complex_t;

typedef struct
{
	double radius;
	double angle;
} polar_t;

complex_t addComplex( complex_t a, complex_t b );
complex_t subtractComplex( complex_t minuend, complex_t subtrahend );
complex_t multiplyComplex( complex_t a, complex_t b );
complex_t divideComplex( complex_t dividend, complex_t divisor );
complex_t conjugateComplex( complex_t c );
double calcRadius( complex_t c );
double calcAngle( complex_t c );
polar_t convertRectangularToPolar( complex_t c );
complex_t convertPolarToRectangular( polar_t p );
complex_t generateTwiddleFactor( int dimension, int nth );

#endif