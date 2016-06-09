#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "bmp.h"
#include "image.h"
#include "dct.h"

Image compressImage( Image img, double threshold, int block_size, bool debug, const char *debug_dct_image );
void printDebugDataToFile( Image_YCC ycc, const char file_name[] );
Matrix* clip( Image_YCC img, int start_y, int start_x, int height, int width );
void update( Image_YCC *img, Matrix *block, int start_y, int start_x, int height, int width );
void reducePixel( Matrix *block, double threshold );

#endif