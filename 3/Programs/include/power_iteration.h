#ifndef POWER_ITERATION_H
#define POWER_ITERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "eigen.h"

Array_Eigen* powerIteration( Matrix* a, double gap );
Matrix* computeNextMatrix( Matrix* prev, Eigen* e_prev );
Eigen* computePower( Matrix* a, Matrix* prev, double gap );

#endif