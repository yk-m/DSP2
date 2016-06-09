#include "dct.h"

Array_d* dct_1d( Array_d* vector ) {
	return computeDCT_1d( vector, false );
}

Array_d* idct_1d( Array_d* vector ) {
	return computeDCT_1d( vector, true );
}

Array_d* computeDCT_1d( Array_d* vector, bool inverse ) {
	Array_d* transformed = newArray_d( vector->length );

	for( int k = 0; k < vector->length; ++k ) {
		transformed->a[k] = 0;

		for ( int n = 0; n < vector->length; ++n ) {
			if ( inverse ) {
				transformed->a[k] += vector->a[n] * generateDCTCoefficient( vector->length, k, n );
				continue;
			}
			transformed->a[k] += vector->a[n] * generateDCTCoefficient( vector->length, n, k );
		}
	}

	return transformed;
}

Matrix* dct_2d( Matrix* m ) {
	return computeDCT_2d( m, false );
}
Matrix* idct_2d( Matrix* m ) {
	return computeDCT_2d( m, true );
}

Matrix* computeDCT_2d( Matrix* m, bool inverse ) {
	Matrix *dct_matrix = generateDCTMatrix( m->row )
	     , *dct_matrix_transposed = transpose( dct_matrix )
	     , *forward, *dcted
	;

	if ( inverse ) {
		forward = multiply( dct_matrix_transposed, m );
		dcted = multiply( forward, dct_matrix );
	} else {
		forward = multiply( dct_matrix, m );
		dcted = multiply( forward, dct_matrix_transposed );
	}

	freeMatrix( forward );
	freeMatrix( dct_matrix );
	freeMatrix( dct_matrix_transposed );
	return dcted;
}

double generateDCTCoefficient( int dim, int n, int k ) {
	if ( k == 0 )
		return sqrt( 1.0/dim );
	return sqrt( 2.0/dim ) * cos( ( 2*n + 1 ) * k * M_PI / 2 / dim );
}

Matrix* generateDCTMatrix( int size ) {
	Matrix* dct_matrix = newMatrix( size, size );

	for ( int k = 0; k < size; ++k ) {
		for ( int n = 0; n < size; ++n ) {
			dct_matrix->a[ n ][ k ] = generateDCTCoefficient( size, k, n );
		}
	}

	return dct_matrix;
}
