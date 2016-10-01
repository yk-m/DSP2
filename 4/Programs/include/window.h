#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <math.h>

#include "array.h"


Array_d* hammingWindow( Array_d* data );
Array_d* hanningWindow( Array_d* data );
Array_d* blackman( Array_d* data );

#endif