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
	int dwt_level, length;
	double threshold, amplitude, frequency, phase, sampling_frequency, gauss_coefficient;

	Array_d *a, *a_out, *a_out2;

	printf(
		"H28年度・DSP2-4・番号32\n"
		"使い方の説明：以下のつの動作モードがあります．\n"
		"             コマンドライン引数argv[n]に適当な引数を渡し，動かしてください．\n"
		"  モード0: DWTを行います．\n"
		"    モード0には出力の違いにより以下のサブモードがあります．\n"
		"      モード0-0: スケーリング係数，ウェーブレット係数をファイル出力\n"
		"        argv[1] = 0（モード指定引数）\n"
		"        argv[2] = 0（サブモード指定引数）\n"
		"        argv[3] = DWTしたいデータのファイルパス\n"
		"        argv[4] = 出力ファイルパス\n"
		"        実行時に，\n"
		"            ・DWTレベル\n"
		"        を聞かれるので入力してください．\n"
		"      モード0-1: 近似関数をファイル出力\n"
		"        argv[1] = 0（モード指定引数）\n"
		"        argv[2] = 1（サブモード指定引数）\n"
		"        argv[3] = DWTしたいデータのファイルパス\n"
		"        argv[4] = 出力ファイルパス\n"
		"        実行時に，\n"
		"            ・DWTレベル\n"
		"        を聞かれるので入力してください．\n"
		"      モード0-2: 誤差成分をファイル出力\n"
		"        argv[1] = 0（モード指定引数）\n"
		"        argv[2] = 2（サブモード指定引数）\n"
		"        argv[3] = DWTしたいデータのファイルパス\n"
		"        argv[4] = 出力ファイルパス\n"
		"        実行時に，\n"
		"            ・DWTレベル\n"
		"        を聞かれるので入力してください．\n"
		"    必要な結果：DWTの結果\n"
		"\n"
		"  モード1: IDWTを行います．\n"
		"    argv[1] = 1（モード指定引数）\n"
		"    argv[2]: IDWTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力ファイルパス\n"
		"    実行時に，\n"
		"        ・DWTレベル\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：IDWTの結果\n"
		"\n"
		"  モード2: DWTによるノイズ除去を行います．\n"
		"    argv[1] = 2（モード指定引数）\n"
		"    argv[2]: ノイズ除去したいデータのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    実行時に，\n"
		"        ・しきい値\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：ノイズ除去の結果\n"
		"\n"
		"  モード3: DFTによるノイズ除去を行います．\n"
		"    argv[1] = 3（モード指定引数）\n"
		"    argv[2]: ノイズ除去したいデータのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    実行時に，\n"
		"        ・しきい値\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：ノイズ除去の結果\n"
		"\n"
		"  モード4: サイン波を出力します．\n"
		"    argv[1] = 4（モード指定引数）\n"
		"    argv[2]: 出力ファイルの名前\n"
		"    実行時に，\n"
		"        ・点数\n"
		"        ・振幅\n"
		"        ・周波数\n"
		"        ・位相\n"
		"        ・サンプリング周波数\n"
		"        ・白色ガウス雑音係数（雑音をのせない場合は0）\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：正弦波\n"
		"\n"
		"  モード5: 矩形波を出力します．\n"
		"    argv[1] = 5（モード指定引数）\n"
		"    argv[2]: 出力ファイルの名前\n"
		"    実行時に，\n"
		"        ・点数\n"
		"        ・振幅\n"
		"        ・周波数\n"
		"        ・位相\n"
		"        ・サンプリング周波数\n"
		"        ・白色ガウス雑音係数（雑音をのせない場合は0）\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：矩形波\n"
		"\n"
	);

	if ( argc < 2 ) {
		printf("引数の数が違います．\n");
		exit( -1 );
	}

	if ( atoi( argv[1] ) == 0 ) {
		if ( argc != 5 ) {
			printf("引数の数が違います．\n");
			exit( -1 );
		}

		printf("\nモード%s-%s\n", argv[1], argv[2] );
		a = loadFileAsArray_d( argv[3], false );
		dwt_level = getNum( "DWTレベル" );
		a_out = dwt( a, dwt_level );
		printResultDWT( a_out, dwt_level );

		if ( atoi( argv[2] ) == 0 ) {
			printArray_dToFile( a_out, argv[4] );
		}
		else if ( atoi( argv[2] ) == 1 ) {
			a_out2 = generateApproximate( a_out, dwt_level );
			printArray_dToFile( a_out2, argv[4] );
			freeArray_d( a_out2 );
		}
		else if ( atoi( argv[2] ) == 2 ) {
			a_out2 = generateErrors( a_out, dwt_level );
			printArray_dToFile( a_out2, argv[4] );
			freeArray_d( a_out2 );
		}
		else {
			printf("モードが正しく設定されていません．\n");
			exit( -1 );
		}

		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi( argv[1] ) == 1 ) {
		if ( argc != 4 ) {
			printf("引数の数が違います．\n");
			exit( -1 );
		}

		printf("\nモード%s\n", argv[1]);
		a = loadFileAsArray_d( argv[2], false );
		dwt_level = getNum( "DWTレベル" );
		a_out = idwt( a, dwt_level );
		printArray_dToFile( a_out, argv[3] );

		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 2 ) {
		if ( argc != 4 ) {
			printf("引数の数が違います．\n");
			exit( -1 );
		}

		printf("\nモード%s\n", argv[1]);
		a = loadFileAsArray_d( argv[2], false );
		threshold = getNum_double( "しきい値(小数値)" );
		a_out = noiseRemovalWithDWT( a, threshold );
		printArray_dToFile( a_out, argv[3] );

		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 3 ) {
		if ( argc != 4 ) {
			printf("引数の数が違います．\n");
			exit( -1 );
		}

		printf("\nモード%s\n", argv[1]);
		a = loadFileAsArray_d( argv[2], false );
		threshold = getNum_double( "しきい値(小数値)" );
		a_out = noiseRemovalWithDFT( a, threshold );
		printArray_dToFile( a_out, argv[3] );

		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 4 ) {
		if ( argc != 3 ) {
			printf("引数の数が違います．\n");
			exit( -1 );
		}

		printf("\nモード%s\n", argv[1]);
		length = getNum("点数");
		amplitude = getNum_double("振幅");
		frequency = getNum_double("周波数");
		phase = getNum_double("位相");
		sampling_frequency = getNum_double("サンプリング周波数");
		gauss_coefficient = getNum_double("白色ガウス雑音係数（雑音をのせない場合は0）");
		a = generateSinWave( length, amplitude, frequency, phase, sampling_frequency );
		a_out = addWhiteGaussianNoise( a, gauss_coefficient );
		printArray_dToFile( a_out, argv[2] );

		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 5 ) {
		if ( argc != 3 ) {
			printf("引数の数が違います．\n");
			exit( -1 );
		}

		printf("\nモード%s\n", argv[1]);
		length = getNum("点数");
		amplitude = getNum_double("振幅");
		frequency = getNum_double("周波数");
		phase = getNum_double("位相");
		sampling_frequency = getNum_double("サンプリング周波数");
		gauss_coefficient = getNum_double("白色ガウス雑音係数（雑音をのせない場合は0）");
		a = generateSquareWave( length, amplitude, frequency, phase, sampling_frequency );
		a_out = addWhiteGaussianNoise( a, gauss_coefficient );
		printArray_dToFile( a_out, argv[2] );

		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	printf("モードが正しく設定されていません．\n");
	exit( -1 );


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

	// const double amplitude = 1e2
	//            , frequency = 5
	//            , phase = 0
	//            , sampling_frequency = 1024
	// ;
	// Array_d *square_wave = generateSquareWave( 1024, amplitude, frequency, phase, sampling_frequency )
	//       , *sin_wave = generateSinWave( 1024, amplitude, frequency, phase, sampling_frequency )
	//       , *noised_square = addWhiteGaussianNoise( square_wave, 10 )
	//       , *noised_sin = addWhiteGaussianNoise( sin_wave, 10 )
	//       , *recovered_square_dft, *recovered_square_dwt
	//       , *recovered_sin_dft, *recovered_sin_dwt
	// ;

	// printArray_dToFile( square_wave, "files/output/square_wave.txt" );
	// printArray_dToFile( sin_wave, "files/output/sin_wave.txt" );
	// printArray_dToFile( noised_square, "files/output/noised_square.txt" );
	// printArray_dToFile( noised_sin, "files/output/noised_sin.txt" );

	// printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( square_wave ) ) ), "files/output/square_wave_spectrum.txt" );
	// printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( sin_wave ) ) ), "files/output/sin_wave_spectrum.txt" );
	// printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( noised_square ) ) ), "files/output/square_wave_n_spectrum.txt" );
	// printArray_dToFile( calcAmplitudeSpectrum( fft( array_dToc( noised_sin ) ) ), "files/output/sin_wave_n_spectrum.txt" );

	// recovered_square_dwt = noiseRemovalWithDWT( noised_square, 70 );
	// recovered_square_dft = noiseRemovalWithDFT( noised_square, 5e3 );
	// recovered_sin_dwt = noiseRemovalWithDWT( noised_sin, 70 );
	// recovered_sin_dft = noiseRemovalWithDFT( noised_sin, 5e3 );

	// printArray_dToFile( recovered_square_dwt, "files/output/recdwt_square_wave.txt" );
	// printArray_dToFile( recovered_square_dft, "files/output/recdft_square_wave.txt" );
	// printArray_dToFile( recovered_sin_dwt, "files/output/recdwt_sin_wave.txt" );
	// printArray_dToFile( recovered_sin_dft, "files/output/recdft_sin_wave.txt" );

	// printArray_dToFile( generateApproximate( dwt( sin_wave, 3 ), 3 ), "files/output/sin_dwt_approximate.txt" );
	// printArray_dToFile( generateErrors( dwt( sin_wave, 3 ), 3 ), "files/output/sin_dwt_errors.txt" );
	// printArray_dToFile( generateApproximate( dwt( square_wave, 3 ), 3 ), "files/output/square_dwt_approximate.txt" );
	// printArray_dToFile( generateErrors( dwt( square_wave, 3 ), 3 ), "files/output/square_dwt_errors.txt" );
	// printArray_dToFile( generateApproximate( dwt( noised_sin, 3 ), 3 ), "files/output/noised_sin_dwt_approximate.txt" );
	// printArray_dToFile( generateErrors( dwt( noised_sin, 3 ), 3 ), "files/output/noised_sin_dwt_errors.txt" );
	// printArray_dToFile( generateApproximate( dwt( noised_square, 3 ), 3 ), "files/output/noised_square_dwt_approximate.txt" );
	// printArray_dToFile( generateErrors( dwt( noised_square, 3 ), 3 ), "files/output/noised_square_dwt_errors.txt" );

	// freeArray_d( square_wave );
	// freeArray_d( sin_wave );
	// freeArray_d( noised_square );
	// freeArray_d( noised_sin );
	// freeArray_d( recovered_square_dwt);
	// freeArray_d( recovered_square_dft);
	// freeArray_d( recovered_sin_dwt);
	// freeArray_d( recovered_sin_dft);
}
