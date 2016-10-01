#include "wave.h"

Array_d* generateSinWave( int length, double amplitude, double frequency, double phase, double sampling_frequency ) {
	return generateCosWave( length, amplitude, frequency, phase-M_PI/2, sampling_frequency );
}

Array_d* generateCosWave( int length, double amplitude, double frequency, double phase, double sampling_frequency ) {
	Array_d* cos_wave = newArray_d( length );
	for ( int n = 0; n < cos_wave->length; ++n ) {
		cos_wave->a[n] = amplitude * cos( 2 * M_PI * frequency * n/sampling_frequency + phase );
	}
	return cos_wave;
}

Array_d* generateSquareWave( int length, double amplitude, double frequency, double phase, double sampling_frequency ) {
	Array_d* square_wave = newArray_d( length );
	for ( int n = 0; n < square_wave->length; ++n ) {
		square_wave->a[n] = amplitude * squareWave( 2 * M_PI * frequency * n/sampling_frequency + phase );
	}
	return square_wave;
}

double squareWave( double theta ) {
	return ( fmod( theta, 2* M_PI ) < M_PI )? 1 : -1;
}

Array_d* generateGaussSignal( int length, double amplitude ) {
	Array_d *signal = newArray_d( length );

	for ( int i = 0; i < signal->length; ++i) {
		signal->a[i] = amplitude * gauss();
	}
	return signal;
}

double gauss( void ) {
	double x1, x2
	     , standard_deviation = 1.0
	;

	x1 = (double)rand() / (RAND_MAX);
	while ( x1 == 0.0 ) {
		x1 = (double)rand() / (RAND_MAX);
	}
	x2 = (double)rand() / (RAND_MAX);

	return sqrt( -2.0 * log(x1) ) * cos( 2.0 * M_PI * x2 ) * sqrt( standard_deviation );
}

Array_d* color( Array_d *noise, double coefficient ) {
	Array_d *colored = newArray_d( noise->length );
	colored->a[0] = noise->a[0];
	for ( int i = 1; i < colored->length; i++ ) {
		colored->a[i] = noise->a[i] + coefficient * noise->a[i-1];
	}
	return colored;
}

Array_d* addWhiteGaussianNoise( Array_d* wave, double noise_level ) {
	Array_d* noised_wave = newArray_d( wave->length );
	for ( int i = 0; i < noised_wave->length; ++i ) {
		noised_wave->a[i] = noise_level*gauss() + wave->a[i];
	}
	return noised_wave;
}
