#include "correlation.h"

Array_d* calcAutoCorrelationFunction( Array_d* original_vector ) {
	// int original_dim = original_vector->length;
	// Array_c *vector = expand( array_dToc( original_vector ) )
	//       , *power_spectrum
	//       , *ffted
	//       , *iffted
	// ;
	// Array_d *auto_correlation_function;

	// ffted = fft( vector );
	// power_spectrum = power_old( ffted );
	// iffted = ifft( power_spectrum );
	// auto_correlation_function = array_cTod( iffted );

	// for ( int i = 0; i < auto_correlation_function->length; i++ ) {
	// 	auto_correlation_function->a[i] /= original_dim;
	// }

	// freeArray_c( vector );
	// freeArray_c( ffted );
	// freeArray_c( iffted );
	// freeArray_c( power_spectrum );
	// return cloneArray_d( auto_correlation_function, original_dim );

	return calcCorrelationFunction( original_vector, original_vector );
}

Array_d* calcCorrelationFunction( Array_d* original_vector1, Array_d *original_vector2 ) {
	int original_dim = original_vector1->length;
	Array_c *vector1, *vector2
	      , *power_spectrum
	      , *ffted1, *ffted2
	      , *iffted
	;
	Array_d *auto_correlation_function;

	if ( original_vector1->length != original_vector2->length ) {
		printf("要素数が違うので相互相関を調べられません．\n");
		exit( -1 );
	}

	vector1 = expand( array_dToc( original_vector1 ) );
	vector2 = expand( array_dToc( original_vector2 ) );
	ffted1 = fft( vector1 );
	ffted2 = fft( vector2 );
	power_spectrum = power( ffted1, ffted2 );
	iffted = ifft( power_spectrum );
	auto_correlation_function = array_cTod( iffted );

	for ( int i = 0; i < auto_correlation_function->length; i++ ) {
		auto_correlation_function->a[i] /= original_dim;
	}

	freeArray_c( vector1 );
	freeArray_c( vector2 );
	freeArray_c( ffted1 );
	freeArray_c( ffted2 );
	freeArray_c( iffted );
	freeArray_c( power_spectrum );
	return cloneArray_d( auto_correlation_function, original_dim );
}

Array_c* power_old( Array_c* vec ) {
	Array_c* power_spectrum = newArray_c( vec->length );
	double radius;
	for( int i = 0; i < vec->length; i++ ) {
		radius = calcRadius( vec->a[i] );
		power_spectrum->a[i].re = radius * radius;
		power_spectrum->a[i].im = 0;
	}
	return power_spectrum;
}

Array_c* power( Array_c* vec1, Array_c* vec2 ) {
	Array_c* power_spectrum = newArray_c( vec1->length );
	for ( int i = 0; i < vec1->length; i++ ) {
		power_spectrum->a[i] = multiplyComplex( conjugateComplex( vec1->a[i] ), vec2->a[i] );
	}
	return power_spectrum;
}

Array_c* expand( Array_c* original_vector ) {
	return cloneArray_c( original_vector, calcDimForFFT( original_vector->length ) );
}

int calcDimForFFT( int original_dim ) {
	int dim = original_dim * 2;
	if ( isPowerOfTwo( dim ) )
		return dim;
	return 2 << intlog2( dim );
}