#include <stdio.h>
#include <time.h>

enum CountStatus { START, STOP, PAUSE };

void countTime( clock_t time, enum CountStatus status );