#include "spectrum.h"

Array_d* calcAmplitudeSpectrum( Array_c* transformed ) {
	Array_d *spectrum = newArray_d( transformed->length );
	for (int k = 0; k < spectrum->length; ++k) {
		spectrum->a[k] = calcRadius( transformed->a[k] );
	}

	return spectrum;
}

Array_d* calcPhaseSpectrum( Array_c* transformed ) {
	Array_d *spectrum = newArray_d( transformed->length );
	for (int k = 0; k < spectrum->length; ++k) {
		spectrum->a[k] = calcAngle( transformed->a[k] );
	}

	return spectrum;
}