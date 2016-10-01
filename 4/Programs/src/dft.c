#include "dft.h"

Array_c* dft( Array_c* data ) {
	return dftInterface( data, true );
}

Array_c* idft( Array_c* transformed ) {
	return dftInterface( transformed, false );
}

Array_c* dftInterface( Array_c* data, bool dft ) {
	Array_c* transformed = newArray_c( data->length );
	double a = ( dft )? 1.0 : -1.0
	     , b = ( dft )? 1.0 : data->length
	;

	for (int k = 0; k < data->length; ++k) {
		transformed->a[k] = calcNthDiscreteFourierTransform( data, a, b, k );
	}

	return transformed;
}

complex_t calcNthDiscreteFourierTransform( Array_c* data, int a, int b, int k ) {
	complex_t Xk = { 0, 0 };

	for ( int n = 0; n < data->length; ++n ) {
		Xk.re += data->a[n].re * cos( 2*M_PI/data->length * n*k ) + a * data->a[n].im * sin( 2*M_PI/data->length * n*k );
		Xk.im += data->a[n].im * cos( 2*M_PI/data->length * n*k ) - a * data->a[n].re * sin( 2*M_PI/data->length * n*k );
	}

	Xk.re /= b;
	Xk.im /= b;

	return Xk;
}
