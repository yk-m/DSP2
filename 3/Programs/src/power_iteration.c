#include "power_iteration.h"

Array_Eigen* powerIteration( Matrix* a, double gap ) {
	Array_Eigen* eigens = newArray_Eigen( a->row );
	Matrix *initial_vector = newIdentityMatrix( a->row, 1 )
	     , *tmp
	;

	eigens->a[0] = computePower( a, initial_vector, gap );
	for ( int i = 1; i < eigens->length; i++ ) {
		tmp = a;
		a = copmuteNextMatrix( a, eigens->a[i-1] );
		eigens->a[i] = computePower( a, initial_vector, gap );

		if ( i != 1 )
			freeMatrix(tmp);
	}

	freeMatrix(a);
	freeMatrix(initial_vector);

	return eigens;
}

Matrix* copmuteNextMatrix( Matrix* prev, Eigen* e_prev ) {
	Matrix *product, *scalar_product, *transposed, *next;

	transposed = transpose( e_prev->vector );
	product = multiply( e_prev->vector, transposed );
	scalar_product = multiplyByScalar( product, e_prev->value );
	next = subtract( prev, scalar_product );

	freeMatrix( transposed );
	freeMatrix( product );
	freeMatrix( scalar_product );

	return next;
}

Eigen* computePower( Matrix* a, Matrix* prev, double gap ) {
	Matrix *next, *product, *diff;
	Eigen* result;
	double error;

	product = multiply( a, prev );
	next = divideByScalar( product, calcNorm( product ) );
	diff = subtract( next, prev );

	error = calcNorm( diff );
	freeMatrix( diff );

	if ( error >= gap ) {
		freeMatrix( product );
		result = computePower( a, next, gap );
		freeMatrix( next );
		return result;
	}

	result = newEigen();
	result->value = dotProduct( prev, product );
	result->vector = next;

	freeMatrix( product );
	return result;
}
