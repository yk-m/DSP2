#ifndef DWT_H
#define DWT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "array.h"
#include "calculation.h"

int calcCoefficientLength( int wave_length, int level );
Array_d* dwt( Array_d* original_wave, int dwt_level );
Array_d* idwt( Array_d* transformed, int dwt_level );

void printResultDWT( Array_d* transformed, int dwt_level );
void printScalingCoefficients( Array_d* transformed, int dwt_level );
void printWaveletCoefficients( Array_d* transformed, int dwt_level );

Array_d* generateApproximate( Array_d* transformed, int dwt_level );
Array_d* generateErrors( Array_d* transformed, int dwt_level );

#endif