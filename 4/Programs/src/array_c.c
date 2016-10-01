#include "array_c.h"

complex_t *allocateComplexMemory( int num )
{
	return (complex_t *) malloc( num * sizeof( complex_t ) );
}

Array_c* newArray_c( int length ) {
	Array_c *d;

	if( ( d = (Array_c*)malloc( sizeof( Array_c ) ) ) == NULL )
		AllocationError();

	if( ( d->a = allocateComplexMemory( length ) ) == NULL )
		AllocationError();

	d->length = length;

	return d;
}

void freeArray_c( Array_c* d ) {
	free( d->a );
	free( d );
}

void printArray_c( Array_c* a ) {
	printf("length: %d\n", a->length);
	for ( int i = 0; i < a->length; i++ ) {
		printf("%f %f\n", a->a[i].re, a->a[i].im );
	}
	printf("\n");
}

int isCloseToZero( double value )
{
	return value < 0.0001 && value > -0.0001;
}

void printArray_cToFile( Array_c* d, const char file_name[] ) {
	FILE *fp = openFile( file_name, "w" );
	if ( fp == NULL )
		FileOpenError( file_name );

	for ( int i = 0; i < d->length; ++i ) {
		fprintf( fp, "%.2f", d->a[i].re );

		if ( isCloseToZero( d->a[i].im ) ){
			fprintf( fp, "\n");
			continue;
		}

		if ( d->a[i].im < 0 )
			fprintf( fp, "-j%f\n", -d->a[i].im );
		else
			fprintf( fp, "+j%f\n", d->a[i].im );
	}

	fclose( fp );
}

Array_c* cloneArray_c( Array_c* vector, int dim ) {
	int i;

	Array_c* new_vector = newArray_c( dim );
	for ( i = 0; i < vector->length && i < new_vector->length; i++ ) {
		new_vector->a[i] = vector->a[i];
	}
	for ( ; i < new_vector->length; i++ ) {
		new_vector->a[i].re = 0;
		new_vector->a[i].im = 0;
	}
	return new_vector;
}

Array_c* array_dToc( Array_d* vector ) {
	Array_c* new_vector = newArray_c( vector->length );
	for ( int i = 0; i < new_vector->length; i++ ) {
		new_vector->a[i].re = vector->a[i];
		new_vector->a[i].im = 0;
	}
	return new_vector;
}

Array_d* array_cTod( Array_c* vector ) {
	Array_d* new_vector = newArray_d( vector->length );
	for ( int i = 0; i < new_vector->length; i++ ) {
		new_vector->a[i] = vector->a[i].re;
	}
	return new_vector;
}
