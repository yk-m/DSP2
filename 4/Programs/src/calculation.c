#include "calculation.h"

int isPowerOfTwo( int value ) {
	return !( value & ( value - 1 ) );
}

int intlog2( int n ) {
	int count = 0;
	while ( n > 1 ) {
		count++;
		n >>= 1;
	}
	return count;
}
