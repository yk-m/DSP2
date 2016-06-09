#include "counter.h"

void countTime( clock_t time, enum CountStatus status  ) {
	static clock_t previous;
	static double total = 0;
	if ( status == START ) {
		previous = time;
		return;
	}
	if ( status == PAUSE ) {
		total += (double)( time - previous )/(double)CLOCKS_PER_SEC;
		return;
	}

	total += (double)( time - previous )/(double)CLOCKS_PER_SEC;
	printf("time: %f\n", total );

	total = 0;
}
