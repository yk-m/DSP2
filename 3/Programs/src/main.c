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

	m = loadFileAsMatrix( argv[1], false );
	r_pi = powerIteration( m, THRESHOLD );
	r_jacobi = jacobi( m, THRESHOLD );

	printf("べき乗法\n");
	printArray_Eigen( r_pi );
	printf("ヤコビ法\n");
	printArray_Eigen( r_jacobi );

	freeMatrix( m );
	freeArray_Eigen( r_pi );
	freeArray_Eigen( r_jacobi );
}
