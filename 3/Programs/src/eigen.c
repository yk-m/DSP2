#include "eigen.h"

Eigen* newEigen() {
	Eigen *e;

	if( ( e = (Eigen*)malloc( sizeof( Eigen ) ) ) == NULL )
		AllocationError();

	return e;
}

void freeEigen( Eigen* e ) {
	freeMatrix( e->vector );
	free( e );
}

void printEigen( Eigen* e ) {
	printf( "Eigen value: %.4f\n", e->value );
	printf( "Eigen vector:\n" );
	for ( int i = 0; i < e->vector->row; i++ ) {
		printf("    | %7.4f |\n", e->vector->a[i][0] );
	}
	printf("\n");
}

Array_Eigen* newArray_Eigen( int length ) {
	Array_Eigen *e;

	if( ( e = (Array_Eigen*)malloc( sizeof( Array_Eigen ) ) ) == NULL )
		AllocationError();

	if( ( e->a = (Eigen**)malloc( sizeof(Eigen*) * length ) ) == NULL )
		AllocationError();

	e->length = length;

	return e;
}

void freeArray_Eigen( Array_Eigen* e ) {
	for ( int i = 0; i < e->length; i++ ) {
		freeEigen( e->a[i] );
	}
	free( e->a );
	free( e );
}

void printArray_Eigen( Array_Eigen* e ) {
	for ( int i = 0; i < e->length; i++ ) {
		printEigen( e->a[i] );
	}
}