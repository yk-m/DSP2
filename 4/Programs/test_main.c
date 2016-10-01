//＊＊＊ H28年度・DSP2-4・番号32 ＊＊＊

#include <stdio.h>
#include <stdbool.h>

#include "array.h"
#include "dft.h"
#include "fft.h"
#include "dwt.h"
#include "noise_removal.h"
#include "wave.h"
#include "calculation.h"

#define INPUT_FILE_NUM 1

int main( int argc, char *argv[] ) {
	// Array_d *input
	//       , *output
	//       , *recovered
	// ;

	// input = loadFileAsArray_d( argv[1], false );
	// output = dwt( input, 3 );
	// recovered = idwt( output, 3 );

	// printResultDWT( output, 3 );
	// printArray_d( recovered );

	// freeArray_d( input );
	// freeArray_d( output );
	// freeArray_d( recovered );

	const double amplitude = 1e2
	           , frequency = 5
	           , phase = 0
	           , sampling_frequency = 1024
	;
	Array_d *square_wave = generateSquareWave( 1024, amplitude, frequency, phase, sampling_frequency )
	      , *sin_wave = generateSinWave( 1024, amplitude, frequency, phase, sampling_frequency )
	      , *noised_square = addWhiteGaussianNoise( square_wave, 10 )
	      , *noised_sin = addWhiteGaussianNoise( sin_wave, 10 )
	      , *recovered_square_dft, *recovered_square_dwt
	      , *recovered_sin_dft, *recovered_sin_dwt
	;

	printArray_dToFile( square_wave, "files/output/square_wave.txt" );
	printArray_dToFile( sin_wave, "files/output/sin_wave.txt" );
	printArray_dToFile( noised_square, "files/output/noised_square.txt" );
	printArray_dToFile( noised_sin, "files/output/noised_sin.txt" );

	printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( square_wave ) ) ), "files/output/square_wave_spectrum.txt" );
	printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( sin_wave ) ) ), "files/output/sin_wave_spectrum.txt" );
	printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( noised_square ) ) ), "files/output/square_wave_n_spectrum.txt" );
	printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( noised_sin ) ) ), "files/output/sin_wave_n_spectrum.txt" );

	recovered_square_dwt = noiseRemovalWithDWT( noised_square, 70 );
	recovered_square_dft = noiseRemovalWithDFT( noised_square, 5e3 );
	recovered_sin_dwt = noiseRemovalWithDWT( noised_sin, 70 );
	recovered_sin_dft = noiseRemovalWithDFT( noised_sin, 5e3 );

	printArray_dToFile( recovered_square_dwt, "files/output/recdwt_square_wave.txt" );
	printArray_dToFile( recovered_square_dft, "files/output/recdft_square_wave.txt" );
	printArray_dToFile( recovered_sin_dwt, "files/output/recdwt_sin_wave.txt" );
	printArray_dToFile( recovered_sin_dft, "files/output/recdft_sin_wave.txt" );

	printArray_dToFile( generateApproximate( dwt( sin_wave, 3 ), 3 ), "files/output/sin_dwt_approximate.txt" );
	printArray_dToFile( generateErrors( dwt( sin_wave, 3 ), 3 ), "files/output/sin_dwt_errors.txt" );
	printArray_dToFile( generateApproximate( dwt( square_wave, 3 ), 3 ), "files/output/square_dwt_approximate.txt" );
	printArray_dToFile( generateErrors( dwt( square_wave, 3 ), 3 ), "files/output/square_dwt_errors.txt" );
	printArray_dToFile( generateApproximate( dwt( noised_sin, 3 ), 3 ), "files/output/noised_sin_dwt_approximate.txt" );
	printArray_dToFile( generateErrors( dwt( noised_sin, 3 ), 3 ), "files/output/noised_sin_dwt_errors.txt" );
	printArray_dToFile( generateApproximate( dwt( noised_square, 3 ), 3 ), "files/output/noised_square_dwt_approximate.txt" );
	printArray_dToFile( generateErrors( dwt( noised_square, 3 ), 3 ), "files/output/noised_square_dwt_errors.txt" );

	freeArray_d( square_wave );
	freeArray_d( sin_wave );
	freeArray_d( noised_square );
	freeArray_d( noised_sin );
	freeArray_d( recovered_square_dwt);
	freeArray_d( recovered_square_dft);
	freeArray_d( recovered_sin_dwt);
	freeArray_d( recovered_sin_dft);
}
