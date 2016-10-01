#ifndef WAVE_H
#define WAVE_H

#include <stdio.h>
#include <math.h>

#include "array.h"


Array_d* generateSinWave( int length, double amplitude, double frequency, double phase, double sampling_frequency );
Array_d* generateCosWave( int length, double amplitude, double frequency, double phase, double sampling_frequency );
Array_d* generateSquareWave( int length, double amplitude, double frequency, double phase, double sampling_frequency );
double squareWave( double theta );
Array_d* generateGaussSignal( int length, double amplitude );
double gauss( void );
Array_d* color( Array_d *noise, double coefficient );
Array_d* addWhiteGaussianNoise( Array_d* wave, double noise_level );

#endif