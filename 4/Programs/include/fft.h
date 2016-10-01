#ifndef FFT_H
#define FFT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"
#include "complex.h"
#include "array.h"
#include "array_c.h"
#include "calculation.h"


Array_c* fft( Array_c *data );
Array_c* ifft( Array_c *data );
Array_c* fftInterface( Array_c *data, Array_c *twiddles, bool fft );
void calcFFT( complex_t *data, complex_t *twiddles, int fft_points );
void sortData( complex_t *data, complex_t *sorted, int fft_points );
void reverseBits( int *bits, int fft_points, int number_of_bits );
void conjugateComplexes( Array_c *comp );
Array_c* generateTwiddleFactors( int fft_points );
Array_d* calcAmplitudeSpectrum( Array_c Xk[] );

#endif