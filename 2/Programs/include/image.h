#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "iof.h"

typedef struct {
	unsigned char blue;			// Bule値
	unsigned char green;		// Green値
	unsigned char red;			// Red値
} RGB_Data;

typedef struct {
	double y;
	double cb;
	double cr;
} YCC_Data;

typedef struct {
	int width;
	int height;
	RGB_Data** data;
} Image;

typedef struct {
	int width;
	int height;
	YCC_Data** data;
} Image_YCC;

Image newImage( int height, int width );
void freeImage( Image img );
Image_YCC newImage_YCC( int height, int width );
void freeImage_YCC( Image_YCC img );
void printImage( Image img );
void printImage_YCC( Image_YCC img );
void printRGB_Data( RGB_Data rgb );
void printYCC_Data( YCC_Data ycc );

Image_YCC convertColorSpaceIntoYCC( Image img );
Image convertColorSpaceIntoRGB( Image_YCC img_ycc );
RGB_Data YCCtoRGB( YCC_Data ycc );
YCC_Data RGBtoYCC( RGB_Data rgb );

#endif