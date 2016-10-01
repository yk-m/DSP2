#include "window.h"

Array_d* hammingWindow( Array_d* data ) {
	Array_d *windowed = newArray_d( data->length );
	for ( int n = 0; n < windowed->length; ++n ) {
		windowed->a[n] = data->a[n] * ( 0.54 - 0.46*cos( 2*M_PI*n / data->length ) );
	}

	return windowed;
}

Array_d* hanningWindow( Array_d* data ) {
	Array_d *windowed = newArray_d( data->length );
	for ( int n = 0; n < windowed->length; ++n ) {
		windowed->a[n] = data->a[n] * ( 0.5 - 0.5*cos( 2*M_PI*n / data->length ) );
	}

	return windowed;
}

Array_d* blackman( Array_d* data ) {
	Array_d *windowed = newArray_d( data->length );
	for ( int n = 0; n < windowed->length; ++n ) {
		windowed->a[n] = data->a[n] * ( 0.42 - 0.5*cos( 2*M_PI*n / data->length ) + 0.08*cos( 4*M_PI*n / data->length ) );
	}

	return windowed;
}