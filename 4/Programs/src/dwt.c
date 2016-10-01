#include "dwt.h"

int calcCoefficientLength( int wave_length, int level ) {
	return wave_length/(1 << level);
}

Array_d* dwt( Array_d* original_wave, int dwt_level ) {
	const double sqrt_2_inverse = 1/sqrt(2);

	Array_d *wave, *transformed;
	int wave_length = original_wave->length
	  , coefficient_length
	  , start_position = wave_length
	;
	double sum, difference;

	if ( !isPowerOfTwo( wave_length ) ) {
		printf("DWTできる要素数ではありません．2のべき乗にしてください．\n");
		exit(-1);
	}

	if ( wave_length < 1 << dwt_level ) {
		printf("レベルが高すぎます．\n");
		exit(-1);
	}

	wave = cloneArray_d( original_wave, wave_length );
	transformed = newArray_d( wave_length );

	for ( int level = 1; level <= dwt_level; ++level ) {
		coefficient_length = calcCoefficientLength( wave_length, level );
		start_position -= coefficient_length;
		for ( int i = 0; i < coefficient_length; ++i ) {
			sum = wave->a[2*i] + wave->a[2*i+1];
			difference = wave->a[2*i] - wave->a[2*i+1];

			transformed->a[i] = sqrt_2_inverse * sum;
			transformed->a[ start_position + i ] = sqrt_2_inverse * difference;
		}
		copyArray_d( transformed, wave );
	}
	freeArray_d( wave );

	return transformed;
}

Array_d* idwt( Array_d* transformed, int dwt_level ) {
	const double sqrt_2_inverse = 1/sqrt(2);

	Array_d *wave = cloneArray_d( transformed, transformed->length )
	      , *recovered = cloneArray_d( transformed, transformed->length )
	;
	int wave_length = transformed->length
	  , coefficient_length
	  , start_position
	;
	double sum, difference;

	for ( int level = dwt_level; level >= 1; --level ) {
		coefficient_length = calcCoefficientLength( wave_length, level );
		for ( int i = 0; i < coefficient_length; ++i ) {
			sum = wave->a[i] + wave->a[coefficient_length+i];
			difference = wave->a[i] - wave->a[coefficient_length+i];

			recovered->a[2*i] = sqrt_2_inverse * sum;
			recovered->a[2*i+1] = sqrt_2_inverse * difference;
		}
		copyArray_d( recovered, wave );
	}

	return recovered;
}

void printResultDWT( Array_d* transformed, int dwt_level ) {
	printf("Coefficients of Scaling\n");
	printScalingCoefficients( transformed, dwt_level );
	printf("Coefficients of Wavelet\n");
	printWaveletCoefficients( transformed, dwt_level );
	printf("\n");
}

void printScalingCoefficients( Array_d* transformed, int dwt_level ) {
	int coefficient_length = calcCoefficientLength( transformed->length, dwt_level );
	for ( int i = 0; i < coefficient_length; ++i ) {
		printf("%lf ", transformed->a[i]);
	}
	printf("\n");
}

void printWaveletCoefficients( Array_d* transformed, int dwt_level ) {
	int coefficient_length, start_position = transformed->length;

	for ( int level = 1; level <= dwt_level; ++level ) {
		printf( "Level %d:\n", level );
		coefficient_length = calcCoefficientLength( transformed->length, level );
		start_position -= coefficient_length;
		for (int i = 0; i < coefficient_length; ++i) {
			printf("%lf ", transformed->a[start_position+i]);
		}
		printf("\n");
	}
}

Array_d* generateApproximate( Array_d* transformed, int dwt_level ) {
	int coefficient_length = calcCoefficientLength( transformed->length, dwt_level )
	  , resolution = 1 << dwt_level
	;
	Array_d *approximate = newArray_d( transformed->length );
	for ( int i = 0; i < coefficient_length; ++i ) {
		for ( int j = 0; j < resolution; ++j ) {
			approximate->a[i*resolution + j] = transformed->a[i];
		}
	}
	return approximate;
}

Array_d* generateErrors( Array_d* transformed, int target_level ) {
	int coefficient_length , start_position
	  , resolution = 1 << target_level
	  , j
	;

	Array_d *errors = newArray_d( transformed->length );
	for ( int level = 1; level <= target_level; ++level ) {
		coefficient_length = calcCoefficientLength( transformed->length, level );
		start_position += coefficient_length;
	}

	for ( int i = 0; i < coefficient_length; ++i ) {
		for ( j = 0; j < resolution/2; ++j ) {
			errors->a[resolution*i + j] = transformed->a[ start_position + i ];
		}
		for ( ; j < resolution; ++j ) {
			errors->a[resolution + j] = -transformed->a[ start_position + i ];
		}
	}
	return errors;
}