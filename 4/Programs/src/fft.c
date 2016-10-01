#include "fft.h"

Array_c* fft( Array_c *data ) {
	Array_c *twiddles = generateTwiddleFactors( data->length )
	      , *transformed
	;

	if ( !isPowerOfTwo( data->length ) ) {
		printf("FFTできる要素数ではありません．2の階乗にしてください．\n");
		exit(-1);
	}

	transformed = fftInterface( data, twiddles, true );
	freeArray_c( twiddles );
	return transformed;
}

Array_c* ifft( Array_c *data ) {
	Array_c *twiddles = generateTwiddleFactors( data->length )
	      , *transformed
	;

	if ( !isPowerOfTwo( data->length ) ) {
		printf("IFFTできる要素数ではありません．2の階乗にしてください．\n");
		exit(-1);
	}

	conjugateComplexes( twiddles );
	transformed = fftInterface( data, twiddles, true );
	for( int i = 0; i < transformed->length; i++ ) {
		transformed->a[i].re /= data->length;
		transformed->a[i].im /= data->length;
	}
	freeArray_c( twiddles );
	return transformed;
}

Array_c* fftInterface( Array_c *data, Array_c *twiddles, bool fft ) {
	Array_c *transformed = newArray_c( data->length );

	sortData( data->a, transformed->a, data->length );
	calcFFT( transformed->a, twiddles->a, data->length );
	return transformed;
}

void calcFFT( complex_t *data, complex_t *twiddles, int fft_points ) {
	int number_of_stage = intlog2( fft_points )
	  , distance = 1
	  , resolution = fft_points/2
	  , upper, lower
	;

	complex_t tmp;

	for ( int stage = 0; stage < number_of_stage; stage++ ) {
		for ( int i = 0; i < distance; i++ ) {
			for ( int j = 0; j < resolution; j++ ) {
				upper = distance * 2 * j + i;
				lower = upper + distance;

				tmp = multiplyComplex( data[ lower ], twiddles[ i * resolution ] );
				data[ lower ] = subtractComplex( data[ upper ], tmp );
				data[ upper ] = addComplex( data[ upper ], tmp );
			}
		}
		distance   *= 2;
		resolution /= 2;
	}
}

void sortData( complex_t *data, complex_t *sorted, int fft_points )
{
	int order[fft_points]
	  , number_of_bits = intlog2( fft_points )
	;

	reverseBits( order, fft_points, number_of_bits );
	for ( int i = 0; i < fft_points; i++ ) {
		sorted[i] = data[ order[i] ];
	}
}

void reverseBits( int *bits, int fft_points, int number_of_bits )
{
	int max = 1;
	bits[0] = 0;
	for ( int i = 0; i < number_of_bits; i++ ) {
		for ( int j = 0; j < max; j++ )
			bits[ j + max ] = bits[j] + fft_points / ( 2 * max );
		max *= 2;
	}
	for ( int i = fft_points/2; i < fft_points; i++ ) {
		bits[i] = bits[ i - fft_points/2 ] + 1;
	}
}

Array_c* generateTwiddleFactors( int fft_points )
{
	Array_c* twiddles = newArray_c( fft_points );
	for ( int i = 0; i < fft_points/2; i++ ) {
		twiddles->a[i] =  generateTwiddleFactor( fft_points, i );
	}
	for ( int i = fft_points/2; i < fft_points; i++ ) {
		twiddles->a[i] =  conjugateComplex( twiddles->a[ i - fft_points/2 ] );
	}
	return twiddles;
}

void conjugateComplexes( Array_c *comp )
{
	for ( int i = 0; i < comp->length; i++ ) {
		comp->a[i] = conjugateComplex( comp->a[i] );
	}
}
