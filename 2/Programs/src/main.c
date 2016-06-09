//＊＊＊ H28年度・DSP2-2・番号32 ＊＊＊

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "iof.h"
#include "dct.h"
#include "image.h"
#include "bmp.h"
#include "compress.h"

#define INPUT_FILE_NUM 3
	// input;	Mode
	//				0: 1D DCT
	//				1: 1D IDCT
	//				2: 2D DCT
	//				3: 2D IDCT
	//				4: BMP compress(2D DCT)
	//				5: BMP compress
	// input;	File name
	// output;	File name
	//

int main( int argc, char *argv[] ) {
	Array_d *a, *a_out;
	Matrix *m, *m_out;
	Image img;
	BMP b;

	int block_size;
	double threshold;
	char file_name[ FN + 10 ];

	printf(
		"H28年度・DSP2-2・番号32\n"
		"使い方の説明：以下の5つの動作モードがあります．\n"
		"             コマンドライン引数argv[n]に適当な引数を渡し，動かしてください．\n"
		"  モード0: 1D DCTを行います．\n"
		"    argv[1] = 0（モード指定引数）\n"
		"    argv[2]: 1D DCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：1D DCTの結果\n"
		"\n"
		"  モード1: 1D IDCTを行います．\n"
		"    argv[1] = 1（モード指定引数）\n"
		"    argv[2]: 1D IDCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：1D IDCTの結果\n"
		"\n"
		"  モード2: 2D DCTを行います．\n"
		"    argv[1] = 2（モード指定引数）\n"
		"    argv[2]: 2D DCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：2D DCTの結果\n"
		"\n"
		"  モード3: 2D IDCTを行います．\n"
		"    argv[1] = 3（モード指定引数）\n"
		"    argv[2]: 2D IDCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：2D IDCTの結果\n"
		"\n"
		"  モード4: BMPを読み込み，圧縮します．圧縮過程の YCC変換後Yを2次元DCTした結果 も出力します．\n"
		"    argv[1] = 4（モード指定引数）\n"
		"    argv[2]: 入力するBMPファイルのパス\n"
		"    argv[3]: 出力ファイルの名前\n"
		"    実行時に，\n"
		"        ・分割するブロックのサイズ（int）\n"
		"        ・しきい値（double）\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：DCT係数\n"
		"               実際に出力されるファイルの名前は argv[3]-bxx_tyy.bmp，argv[3](dct)-bxx_tyy.txt です．\n"
		"               （ただし，xx:入力されたブロックのサイズ，yy:入力されたしきい値）\n"
		"\n"
		"  モード5: BMPを読み込み，圧縮します．\n"
		"    argv[1] = 5（モード指定引数）\n"
		"    argv[2]: 入力するBMPファイルのパス\n"
		"    argv[3]: 出力ファイルの名前\n"
		"    実行時に，\n"
		"        ・分割するブロックのサイズ（int）\n"
		"        ・しきい値（dobule）\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：DCTの結果画像\n"
		"               実際に出力されるファイルの名前は argv[3]-bxx_tyy.bmp です．\n"
		"               （ただし，xx:入力されたブロックのサイズ，yy:入力されたしきい値）\n"
		"\n"
	);

	if ( argc != INPUT_FILE_NUM + 1 ) {
		printf("引数の数が違います．\n");
		exit( -1 );
	}

	if ( atoi( argv[1] ) == 0 ) {
		printf("\nモード%s...", argv[1]);
		a = loadFileAsArray_d( argv[2], false );
		a_out = dct_1d( a );
		printArray_dToFile( a_out, argv[3] );
		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi( argv[1] ) == 1 ) {
		printf("\nモード%s...", argv[1]);
		a = loadFileAsArray_d( argv[2], false );
		a_out = idct_1d( a );
		printArray_dToFile( a_out, argv[3] );
		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 2 ) {
		printf("\nモード%s...", argv[1]);
		m = loadFileAsMatrix( argv[2], false );
		m_out = dct_2d( m );
		printMatrixToFile( m_out, argv[3] );
		freeMatrix( m );
		freeMatrix( m_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 3 ) {
		printf("\nモード%s...", argv[1]);
		m = loadFileAsMatrix( argv[2], false );
		m_out = idct_2d( m );
		printMatrixToFile( m_out, argv[3] );
		freeMatrix( m );
		freeMatrix( m_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 4 ) {
		printf("\nモード%s\n\n", argv[1]);
		b = loadFileAsBMP( argv[2], false );
		printBMPFileHeader( b.file_header );
		printBMPInfoHeader( b.info_header );
		printf("\n");
		threshold = getNum_double( "しきい値(小数値)" );
		block_size = getNum( "分割ブロックサイズ(整数値)" );
		sprintf( file_name, "%s(dct)-b%d_t%.1f.txt", argv[3], block_size, threshold );
		img = compressImage( b.img, threshold, block_size, true, file_name );
		freeBMP( b );
		b = newBMP( img );
		sprintf( file_name, "%s-b%d_t%.1f.bmp", argv[3], block_size, threshold );
		createBMPFile( b, file_name );
		freeBMP( b );
		printf("completed!\n");
		return 0;

	}

	if ( atoi(argv[1]) == 5 ) {
		printf("\nモード%s\n\n", argv[1]);
		b = loadFileAsBMP( argv[2], false );
		printBMPFileHeader( b.file_header );
		printBMPInfoHeader( b.info_header );
		printf("\n");
		threshold = getNum_double( "しきい値(小数値)" );
		block_size = getNum( "分割ブロックサイズ(整数値)" );
		img = compressImage( b.img, threshold, block_size, false, "" );
		freeBMP( b );
		b = newBMP( img );
		sprintf( file_name, "%s-b%d_t%.1f.bmp", argv[3], block_size, threshold );
		createBMPFile( b, file_name );
		freeBMP( b );
		printf("completed!\n");
		return 0;
	}

	printf("モードが正しく設定されていません．\n");
	return -1;
}
