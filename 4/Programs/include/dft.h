#ifndef DFT_H
#define DFT_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "complex.h"
#include "array.h"
#include "array_c.h"


Array_c* dft( Array_c* data );
Array_c* idft( Array_c* transformed );
Array_c* dftInterface( Array_c* data, bool dft );
complex_t calcNthDiscreteFourierTransform( Array_c* data, int a, int b, int k );

Array_d* calcAmplitudeSpectrum( Array_c* transformed );
Array_d* calcPhaseSpectrum( Array_c* transformed );

#endif