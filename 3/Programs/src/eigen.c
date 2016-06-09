#include "eigen.h"

Eigen* newEigen( int row, bool init ) {
	Eigen *e;

	if( ( e = (Eigen*)malloc( sizeof( Eigen ) ) ) == NULL )
		AllocationError();

	if ( !init )
		return e;

	e->vector = newMatrix( row, 0 );
	e->vector->a[0][0] = 1;
	for ( int i = 1; i < e->vector->row; ++i ) {
		e->vector->a[i][0] = 0;
	}

	return e;
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
	free( e->a );
	free( e );
}