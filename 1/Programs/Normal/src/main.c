//＊＊＊ H28年度・DSP2-1・番号32 ＊＊＊

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "array.h"
#include "array_c.h"
#include "correlation.h"

int main( int argc, char *argv[] ) {
	Array_d *input1, *input2, *input3, *output1, *output2;

	printf(
		"H28年度・DSP2-1・番号32\n"
		"使い方の説明：v0, v1のデータについて相互相関関数，v2のデータについて自己相関関数を求めます．\n"
		"  argv[n]に以下のデータを渡してください．\n"
		"    n=1 : v0のデータファイル名\n"
		"    n=2 : v1のデータファイル名\n"
		"    n=3 : v2のデータファイル名\n"
		"    n=4 : 相互相関関数の出力ファイル名\n"
		"    n=5 : 自己相関関数の出力ファイル名\n"
		"必要な結果：\n"
		"    ファイル出力：\n"
		"      1\n"
		"        ファイル名：argv[4]\n"
		"        内容：相互相関関数の結果\n"
		"      2\n"
		"        ファイル名：argv[5]\n"
		"        内容：自己相関関数の結果\n"
		"\n"
	);

	if ( argc != 6 ) {
		printf("引数の数が違います．\n");
		exit( -1 );
	}

	input1 = loadFileAsArray_d( argv[1], false );
	input2 = loadFileAsArray_d( argv[2], false );
	input3 = loadFileAsArray_d( argv[3], false );
	output1 = calcCorrelationFunction( input1, input2 );
	output2 = calcAutoCorrelationFunction( input3 );
	printArray_dToFile( output1, argv[4] );
	printArray_dToFile( output2, argv[5] );

	freeArray_d( input1 );
	freeArray_d( input2 );
	freeArray_d( input3 );
	freeArray_d( output1 );
	freeArray_d( output2 );
}


