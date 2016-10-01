#ifndef NOISE_REMOVAL_H
#define NOISE_REMOVAL_H

#include <stdio.h>
#include <math.h>

#include "array.h"
#include "array_c.h"
#include "dft.h"
#include "dwt.h"


Array_d* noiseRemovalWithDFT( Array_d* original_wave, double threshold );
Array_d* noiseRemovalWithDWT( Array_d* original_wave, double threshold );

#endif