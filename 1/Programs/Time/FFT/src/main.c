#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "array.h"
#include "array_c.h"
#include "correlation.h"
#include "counter.h"

// enum CountStatus { START, FINISH, STOCK };

// void countTime( clock_t time, enum CountStatus status  ) {
// 	static clock_t previous;
// 	static double total = 0;
// 	if ( status == START ) {
// 		previous = time;
// 		return;
// 	}
// 	if ( status == STOCK ) {
// 		total += (double)( time - previous )/(double)CLOCKS_PER_SEC;
// 		return;
// 	}

// 	total += (double)( time - previous )/(double)CLOCKS_PER_SEC;
// 	printf("time: %f\n", total );
// }

int main( int argc, char *argv[] ) {
	Array_d *input1, *input2, *input3, *output1, *output2;

	if ( argc != 6 ) {
		printf("引数の数が違います．\n");
		exit( -1 );
	}

	input1 = loadFileAsArray_d( argv[1], false );
	input2 = loadFileAsArray_d( argv[2], false );
	input3 = loadFileAsArray_d( argv[3], false );

	printf("自己相関 %s\n", argv[3] );
	countTime( clock(), START );
	output2 = calcAutoCorrelationFunction( input3 );
	countTime( clock(), STOP );

	printf("相互相関 %s, %s\n", argv[1], argv[2] );
	countTime( clock(), START );
	output1 = calcCorrelationFunction( input1, input2 );
	countTime( clock(), STOP );

	printArray_dToFile( output1, argv[4] );
	printArray_dToFile( output2, argv[5] );

	freeArray_d( input1 );
	freeArray_d( input2 );
	freeArray_d( input3 );
	freeArray_d( output1 );
	freeArray_d( output2 );
}


