#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <stdio.h>
#include <math.h>

#include "array.h"
#include "array_c.h"
#include "complex.h"


Array_d* calcAmplitudeSpectrum( Array_c* transformed );
Array_d* calcPhaseSpectrum( Array_c* transformed );

#endif