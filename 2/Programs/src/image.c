#include "image.h"

Image newImage( int height, int width ) {
	Image img;

	if( ( img.data = (RGB_Data**)malloc( sizeof(RGB_Data*) * height ) ) == NULL )
		AllocationError();

	for ( int i = 0; i < height; ++i ) {
		if( ( img.data[i] = (RGB_Data*)malloc( sizeof(RGB_Data) * width ) ) == NULL )
			AllocationError();
	}

	img.height = height;
	img.width = width;

	return img;
}

void freeImage( Image img ) {
	for ( int i = 0; i < img.height; ++i ) {
		free( img.data[i] );
	}
	free( img.data );
}

Image_YCC newImage_YCC( int height, int width ) {
	Image_YCC img;

	if( ( img.data = (YCC_Data**)malloc( sizeof(YCC_Data*) * height ) ) == NULL )
		AllocationError();

	for ( int i = 0; i < height; ++i ) {
		if( ( img.data[i] = (YCC_Data*)malloc( sizeof(YCC_Data) * width ) ) == NULL )
			AllocationError();
	}

	img.height = height;
	img.width = width;

	return img;
}

void freeImage_YCC( Image_YCC img ) {
	for ( int i = 0; i < img.height; ++i ) {
		free( img.data[i] );
	}
	free( img.data );
}

void printImage( Image img ) {
	printf("Image %d * %d\n", img.height, img.width);
	for ( int h = 0; h < img.height; ++h ) {
		for ( int w = 0; w < img.width; ++w ) {
			printRGB_Data( img.data[h][w] );
			printf(" ");
		}
		printf("\n");
	}
}

void printImage_YCC( Image_YCC img ) {
	printf("Image %d * %d\n", img.height, img.width);
	for ( int h = 0; h < img.height; ++h ) {
		for ( int w = 0; w < img.width; ++w ) {
			printYCC_Data( img.data[h][w] );
			printf(" ");
		}
		printf("\n");
	}
}

void printRGB_Data( RGB_Data rgb ) {
	printf("(%d,%d,%d)", rgb.red, rgb.green, rgb.blue );
}

void printYCC_Data( YCC_Data ycc ) {
	printf("(%f,%f,%f)", ycc.y, ycc.cb, ycc.cr );
}

Image_YCC convertColorSpaceIntoYCC( Image img ) {
	Image_YCC img_ycc = newImage_YCC( img.height, img.width );
	for ( int h = 0; h < img_ycc.height; ++h ) {
		for ( int w = 0; w < img_ycc.width; w++ ) {
			img_ycc.data[h][w] = RGBtoYCC( img.data[h][w] );
		}
	}
	return img_ycc;
}

Image convertColorSpaceIntoRGB( Image_YCC img_ycc ) {
	Image img = newImage( img_ycc.height, img_ycc.width );
	for ( int h = 0; h < img.height; ++h ) {
		for ( int w = 0; w < img.width; w++ ) {
			img.data[h][w] = YCCtoRGB( img_ycc.data[h][w] );
		}
	}
	return img;
}

RGB_Data YCCtoRGB( YCC_Data ycc ) {
	RGB_Data rgb = {
		ycc.y + 1.402*ycc.cr
	  , ycc.y - 0.344*ycc.cb - 0.714*ycc.cr
	  , ycc.y - 1.772*ycc.cb
	};

	return rgb;
}

YCC_Data RGBtoYCC( RGB_Data rgb ) {
	YCC_Data ycc = {
		 0.299*rgb.red + 0.587*rgb.green + 0.114*rgb.blue
	   ,-0.169*rgb.red - 0.331*rgb.green + 0.500*rgb.blue
	   , 0.500*rgb.red - 0.419*rgb.green - 0.081*rgb.blue
	};

	return ycc;
}

