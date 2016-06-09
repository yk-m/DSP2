#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "error.h"
#include "iof.h"
#include "binary.h"
#include "image.h"

#pragma pack(1)
typedef struct TagBITMAPFILEHEADER {
	uint16_t bfType;			// ファイルタイプ("BM"：0x4D42が入る)
	uint32_t bfSize;			// ファイルサイズ
	uint16_t bfReserved1;		// 予約領域（0）
	uint16_t bfReserved2;		// 予約領域（0）
	uint32_t bfOffBits;			// ファイル先頭からみたデータの位置（byte）
} BMPFileHeader;
#pragma pack()

typedef struct {
	uint32_t biSize;			// BITMAPINFOHEADERのサイズ（40[byte]）
	int32_t  biWidth;			// 幅（ピクセル）
	int32_t  biHeight;			// 高さ（ピクセル）
	uint16_t biPlanes;			// カラープレーン数（1）
	uint16_t biBitCount;		// ビクセル当たりビット数（1,4,8,24,32bit）
	uint32_t biCompression;		// 圧縮（0：なし）
	uint32_t biSizeimage;		// 画像データサイズ（[byte]：0でよい）
	int32_t  biXPixPerMeter;	// 水平解像度：m当たり画素数（ピクセル：0でよい）
	int32_t  biYPixPerMeter;	// 垂直解像度：m当たり画素数（ピクセル：0でよい）
	uint32_t biClrUsed;			// カラーパレット数:色数（0でよい）
	uint32_t biClrImportant;	// 重要なカラーインデックス数（0でよい）
} BMPInfoHeader;

typedef struct {
	unsigned char blue;			// Bule値
	unsigned char green;		// Green値
	unsigned char red;			// Red値
	unsigned char re;			// Reserve値
} RGBQUAD;

typedef struct {
	BMPFileHeader file_header;
	BMPInfoHeader info_header;
	Image img;
} BMP;

BMP newBMP( Image img );
void freeBMP( BMP b );
BMPFileHeader newBMPFileHeader( int height, int width );
BMPInfoHeader newBMPInfoHeader( int height, int width );

BMP loadFileAsBMP( const char file[], bool ask_filename );
BMPFileHeader loadBMPFileHeader( FILE* fp );
void printBMPFileHeader( BMPFileHeader h );
BMPInfoHeader loadBMPInfoHeader( FILE* fp );
void printBMPInfoHeader( BMPInfoHeader h );
Image loadImage( FILE* fp, int height, int width );
RGB_Data loadRGBData( FILE* fp );

void createBMPFile( BMP b, const char file_name[] );

#endif