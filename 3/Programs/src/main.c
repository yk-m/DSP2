//＊＊＊ H28年度・DSP2-3・番号32 ＊＊＊

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "matrix.h"
#include "eigen.h"
#include "jacobi.h"
#include "power_iteration.h"

#define INPUT_FILE_NUM 1
#define THRESHOLD 0.0001

int main( int argc, char *argv[] ) {
	Matrix *m;
	Array_Eigen *r_pi, *r_jacobi;

	printf(
		"H28年度・DSP2-3・番号32\n"
		"使い方の説明：コマンドライン引数argv[1]に固有値・固有ベクトルを求めたい行列のファイル名を渡してください．\n"
		"必要な結果：\n"
		"    ヤコビ法・べき乗法それぞれで求めた固有値・固有ベクトルが表示されます．\n"
	);

	m = loadFileAsMatrix( argv[1], false );

	r_jacobi = jacobi( m, THRESHOLD );
	printf("ヤコビ法\n");
	printArray_Eigen( r_jacobi );

	r_pi = powerIteration( m, THRESHOLD );
	printf("べき乗法\n");
	printArray_Eigen( r_pi );

	freeMatrix( m );
	freeArray_Eigen( r_pi );
	freeArray_Eigen( r_jacobi );
}
