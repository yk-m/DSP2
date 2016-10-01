#include "noise_removal.h"

Array_d* noiseRemovalWithDFT( Array_d* original_wave, double threshold ) {
	Array_c *wave_c = array_dToc( original_wave )
	      , *transformed_c = dft( wave_c )
	      , *removed_c
	;
	Array_d *removed;

	for ( int i = 0; i < transformed_c->length; ++i ) {
		if ( calcRadius( transformed_c->a[i] ) < threshold ) {
			transformed_c->a[i].re = 0;
			transformed_c->a[i].im = 0;
		}
	}
	removed_c = idft( transformed_c );
	removed = array_cTod( removed_c );

	freeArray_c( wave_c );
	freeArray_c( transformed_c );
	freeArray_c( removed_c );
	return removed;
}

Array_d* noiseRemovalWithDWT( Array_d* original_wave, double threshold ) {
	Array_d *transformed = dwt( original_wave, intlog2( original_wave->length ) )
	      , *removed
	;

	for ( int i = 1; i < transformed->length; ++i ) {
		if ( fabs( transformed->a[i] ) < threshold )
			transformed->a[i] = 0;
	}
	removed = idwt( transformed, intlog2( transformed->length ) );

	freeArray_d( transformed );
	return removed;
}
