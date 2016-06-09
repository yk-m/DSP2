#ifndef ARRAY_C_H
#define ARRAY_C_H

#include <stdio.h>

#include "iof.h"
#include "error.h"
#include "complex.h"
#include "array.h"

typedef struct {
	complex_t *a;
	int length;
} Array_c;

Array_c* newArray_c( int length );
void freeArray_c( Array_c* c );
void printArray_c( Array_c* a );
void printArray_cToFile( Array_c* c, const char file_name[] );
Array_c* cloneArray_c( Array_c* vector, int dim );
Array_c* array_dToc( Array_d* vector );
Array_d* array_cTod( Array_c* vector );

#endif