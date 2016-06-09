#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "iof.h"
#include "error.h"

typedef struct {
	int *a;
	int length;
} Array_i;

typedef struct {
	double *a;
	int length;
} Array_d;

Array_d* newArray_d( int length );
void freeArray_d( Array_d* d );
Array_d* cloneArray_d( Array_d* vector, int dim );
Array_d* loadFileAsArray_d( const char file[], bool ask_filename );
void printArray_d( Array_d* a );
void printArray_dToFile( Array_d* d, const char file_name[] );

Array_i* newArray_i( int length );
void freeArray_i( Array_i* d );
Array_i* loadFileAsArray_i( const char file[], bool ask_filename );
void printArray_i( Array_i* a );
void printArray_iToFile( Array_i* d, const char file_name[] );

#endif