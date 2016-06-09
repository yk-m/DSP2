#include "bmp.h"

BMP newBMP( Image img ) {
	BMP b;
	b.file_header = newBMPFileHeader( img.height, img.width );
	b.info_header = newBMPInfoHeader( img.height, img.width );
	b.img = img;
	return b;
}

void freeBMP( BMP b ) {
	freeImage( b.img );
	return;
}

BMPFileHeader newBMPFileHeader( int height, int width ) {
	BMPFileHeader h;
	h.bfType      = 0x4d42;
	h.bfReserved1 = 0;
	h.bfReserved2 = 0;
	h.bfOffBits   = 54;
	h.bfSize      = width*3 * height + h.bfOffBits;

	return h;
}

BMPInfoHeader newBMPInfoHeader( int height, int width ) {
	BMPInfoHeader h;
	h.biSize         = 40;
	h.biWidth        = width;
	h.biHeight       = height;
	h.biPlanes       = 1;
	h.biBitCount     = 24;
	h.biCompression  = 0;
	h.biSizeimage    = width*3 * height;
	h.biXPixPerMeter = 0;
	h.biYPixPerMeter = 0;
	h.biClrUsed      = 0;
	h.biClrImportant = 0;

	return h;
}

BMP loadFileAsBMP( const char file[], bool ask_filename ) {
	FILE *fp;
	BMP b;

	char file_name[FN]
	   , line[FN]
	   , *ends
	;
	int row, column;

	if ( ask_filename ) {
		printf( "%s", file );
		askForFilename( file_name );
	}
	else
		strcpy( file_name, file );

	fp = openFile( file_name, "rb" );

	b.file_header = loadBMPFileHeader( fp );
	b.info_header = loadBMPInfoHeader( fp );
	b.img = loadImage( fp, b.info_header.biHeight, b.info_header.biWidth );

	fclose( fp );
	return b;
}

BMPFileHeader loadBMPFileHeader( FILE* fp ) {
	BMPFileHeader header;
	if ( fread( &header, sizeof( header ), 1, fp ) != 1 )
		FileReadError( "BMPFileHeader" );
	return header;
}

void printBMPFileHeader( BMPFileHeader h ) {
	printf(
		"# BMP File Header\n"
		" - File type: 0x%04x\n"
		" - File size: %d\n"
		" - Reserved: %d\n"
		" - Reserved: %d\n"
		" - Offset: %d\n"
		, h.bfType, h.bfSize, h.bfReserved1, h.bfReserved2, h.bfOffBits
	);
}

BMPInfoHeader loadBMPInfoHeader( FILE* fp ) {
	BMPInfoHeader header;
	if ( fread( &header, sizeof( header ), 1, fp ) != 1 )
		FileReadError( "BMPInfoHeader" );
	return header;
}

void printBMPInfoHeader( BMPInfoHeader h ) {
	printf(
		"# BMP Info Header\n"
		" - header size: %d\n"
		" - width in pixels: %d\n"
		" - height in pixels: %d\n"
		" - number of color planes: %d\n"
		" - number of bits per pixel: %d\n"
		" - compression method being used: %d\n"
		" - image size: %d\n"
		" - horizontal resolution of the image: %d\n"
		" - vertical resolution of the image: %d\n"
		" - number of colors in the color palette: %d\n"
		" - number of important colors used: %d\n"
		, h.biSize, h.biWidth, h.biHeight, h.biPlanes, h.biBitCount
		, h.biCompression , h.biSizeimage , h.biXPixPerMeter , h.biYPixPerMeter , h.biClrUsed
		, h.biClrImportant
	);
}

Image loadImage( FILE* fp, int height, int width ) {
	Image img = newImage( height, width );
	int gap = (width * 3 % 4 == 0) ? 0 : 4 - (width * 3 % 4);
	char tmp;
	for ( int h = 0; h < img.height; ++h ) {
		for ( int w = 0; w < img.width; ++w ) {
			img.data[h][w] = loadRGBData( fp );
		}

		for (int i = 0; i < gap; ++i) {
			fread( &tmp, 1, 1, fp );
		}
	}
	return img;
}

RGB_Data loadRGBData( FILE* fp ) {
	RGB_Data rgb;
	if ( fread( &rgb, sizeof( rgb ), 1, fp ) != 1 )
		FileReadError( "RGB_Data" );
	return rgb;
}

void createBMPFile( BMP b, const char file_name[] ) {
	FILE *fp = openFile( file_name, "wb" );

	if ( fwrite( &b.file_header, sizeof( BMPFileHeader ), 1, fp ) != 1 )
		FileWriteError( "BMPFileHeader" );
	if ( fwrite( &b.info_header, sizeof( BMPInfoHeader ), 1, fp ) != 1 )
		FileWriteError( "BMPInfoHeader" );
	for ( int h = 0; h < b.img.height; ++h ) {
		for ( int w = 0; w < b.img.width; ++w ) {
			if ( fwrite( &b.img.data[h][w], sizeof( b.img.data[h][w] ), 1, fp ) != 1 )
				FileWriteError( "Image Data" );
		}
	}

	fclose( fp );
}

