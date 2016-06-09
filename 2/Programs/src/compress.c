#include "compress.h"

Image compressImage( Image img, double threshold, int block_size, bool debug, const char *debug_dct_image ) {
	Matrix *block, *dcted, *idcted;
	Image compressed, img_rgbdebug;
	Image_YCC img_ycc, img_debug;

	if ( block_size == 0 || img.height % block_size + img.width % block_size != 0 ) {
		printf("画像サイズに対し分割ブロックサイズが適正ではありません．\n");
		exit(-1);
	}

	img_ycc = convertColorSpaceIntoYCC( img );
	img_debug = newImage_YCC( img.height, img.width );

	for ( int y = 0; y < img.height/block_size; y++ ) {
		for ( int x = 0; x < img.width/block_size; x++ ) {
			block = clip( img_ycc, y*block_size, x*block_size, block_size, block_size );
			dcted = dct_2d( block );
			reducePixel( dcted, threshold );
			update( &img_debug, dcted, y*block_size, x*block_size, block_size, block_size );
			idcted = idct_2d( dcted );
			update( &img_ycc, idcted, y*block_size, x*block_size, block_size, block_size );

			freeMatrix( block );
			freeMatrix( dcted );
			freeMatrix( idcted );
		}
	}

	compressed = convertColorSpaceIntoRGB( img_ycc );
	freeImage_YCC( img_ycc );

	if ( debug ) {
		printDebugDataToFile( img_debug, debug_dct_image );
		freeImage_YCC( img_debug );
	}

	return compressed;
}

void printDebugDataToFile( Image_YCC ycc, const char file_name[] ) {
	FILE *fp = openFile( file_name, "w" );

	for ( int h = 0; h < ycc.height; ++h ) {
		for ( int w = 0; w < ycc.width; ++w ) {
			fprintf( fp, "%f ", ycc.data[h][w].y );
		}
		fprintf( fp, "\n" );
	}

	fclose( fp );
}

Matrix* clip( Image_YCC img, int start_y, int start_x, int height, int width ) {
	Matrix *block = newMatrix( height, width );
	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			block->a[y][x] = img.data[ start_y + y ][ start_x + x ].y;
		}
	}
	return block;
}

void update( Image_YCC *img, Matrix *block, int start_y, int start_x, int height, int width ) {
	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; ++x ) {
			img->data[ start_y + y ][ start_x + x ].y = block->a[y][x];
		}
	}
}

void reducePixel( Matrix *block, double threshold ) {
	static int count = 0;
	for ( int y = 0; y < block->row; y++ ) {
		for ( int x = 0; x < block->column; ++x ) {
			if ( fabs( block->a[y][x] ) > threshold )
				continue;
			block->a[y][x] = 0;
		}
	}
}

// --- count
// void reducePixel( Matrix *block, double threshold ) {
// 	static int count = 0;
// 	for ( int y = 0; y < block->row; y++ ) {
// 		for ( int x = 0; x < block->column; ++x ) {
// 			if ( fabs( block->a[y][x] ) > threshold )
// 				continue;
// 			block->a[y][x] = 0;
// 			count++;
// 		}
// 	}
// 	printf("%d\n", count);
// }
