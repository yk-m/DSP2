//＊＊＊ H28年度・DSP2-2・番号32 ＊＊＊

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


void FileOpenError( const char* file_name );
void FileReadError( const char* value );
void FileWriteError( const char* value );
void AllocationError();
void DataNumError();


#define FN 1024

int countLinesOfFile( const char file_name[] );
void askForFilename( char file_name[] );
int getNum( char description[] );
double getNum_double( char description[] );
FILE* openFile( const char file_name[], const char* mode );


typedef struct {
	int *a;
	int length;
} Array_i;

typedef struct {
	double *a;
	int length;
} Array_d;

Array_d* newArray_d( int length );
void freeArray_d( Array_d* d );
Array_d* cloneArray_d( Array_d* vector, int dim );
Array_d* loadFileAsArray_d( const char file[], bool ask_filename );
void printArray_d( Array_d* a );
void printArray_dToFile( Array_d* d, const char file_name[] );

Array_i* newArray_i( int length );
void freeArray_i( Array_i* d );
Array_i* loadFileAsArray_i( const char file[], bool ask_filename );
void printArray_i( Array_i* a );
void printArray_iToFile( Array_i* d, const char file_name[] );


typedef struct {
	double **a;
	int row;
	int column;
} Matrix;

Matrix* newMatrix( int row, int column );
void freeMatrix( Matrix* d );

Matrix *loadFileAsMatrix( const char file[], bool ask_filename );
void determineDimensionOfMatrix( const char file_name[], int* row, int* column );
int countSplitter( const char* string, const char splitter );

void printMatrix( Matrix* a );
void printMatrixToFile( Matrix* a, const char file_name[] );

Matrix *multiply( Matrix *a, Matrix *b );
Matrix *transpose( Matrix* m );

void MatrixLoadError();
void InvalidMatrixFormatError();


void loadCharacters( FILE* fp, char* chars, int length );
long loadLongValue( FILE* fp );
long toLong( char s[] );
unsigned long loadUnsignedLongValue( FILE* fp );
unsigned long toUnsignedLong( char s[] );
short loadShortValue( FILE *fp );
unsigned short loadUnsignedShortValue( FILE* fp );
unsigned short toUnsignedShort( char s[] );

void writeCharacters( FILE* fp, const char* chars, int length );
void writeLongValue( FILE* fp, unsigned long d );
void writeShortValue( FILE* fp, unsigned short d );


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


Array_d* dct_1d( Array_d* vector );
Array_d* idct_1d( Array_d* vector );
Array_d* computeDCT_1d( Array_d* vector, bool inverse );

Matrix* dct_2d( Matrix* m );
Matrix* idct_2d( Matrix* m );
Matrix* computeDCT_2d( Matrix* m, bool inverse );

double generateDCTCoefficient( int dim, int n, int k );
Matrix* generateDCTMatrix( int size );


Image compressImage( Image img, double threshold, int block_size, bool debug, const char *debug_dct_image );
void printDebugDataToFile( Image_YCC ycc, const char file_name[] );
Matrix* clip( Image_YCC img, int start_y, int start_x, int height, int width );
void update( Image_YCC *img, Matrix *block, int start_y, int start_x, int height, int width );
void reducePixel( Matrix *block, double threshold );


#define INPUT_FILE_NUM 3
	// input;	Mode
	//				0: 1D DCT
	//				1: 1D IDCT
	//				2: 2D DCT
	//				3: 2D IDCT
	//				4: BMP compress(2D DCT)
	//				5: BMP compress
	// input;	File name
	// output;	File name
	//

int main( int argc, char *argv[] ) {
	Array_d *a, *a_out;
	Matrix *m, *m_out;
	Image img;
	BMP b;

	int block_size;
	double threshold;
	char file_name[ FN + 10 ];

	printf(
		"H28年度・DSP2-2・番号32\n"
		"使い方の説明：以下の5つの動作モードがあります．\n"
		"             コマンドライン引数argv[n]に適当な引数を渡し，動かしてください．\n"
		"  モード0: 1D DCTを行います．\n"
		"    argv[1] = 0（モード指定引数）\n"
		"    argv[2]: 1D DCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：1D DCTの結果\n"
		"\n"
		"  モード1: 1D IDCTを行います．\n"
		"    argv[1] = 1（モード指定引数）\n"
		"    argv[2]: 1D IDCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：1D IDCTの結果\n"
		"\n"
		"  モード2: 2D DCTを行います．\n"
		"    argv[1] = 2（モード指定引数）\n"
		"    argv[2]: 2D DCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：2D DCTの結果\n"
		"\n"
		"  モード3: 2D IDCTを行います．\n"
		"    argv[1] = 3（モード指定引数）\n"
		"    argv[2]: 2D IDCTしたいベクトルのファイルパス\n"
		"    argv[3]: 出力テキストファイルパス\n"
		"    必要な結果：2D IDCTの結果\n"
		"\n"
		"  モード4: BMPを読み込み，圧縮します．圧縮過程の YCC変換後Yを2次元DCTした結果 も出力します．\n"
		"    argv[1] = 4（モード指定引数）\n"
		"    argv[2]: 入力するBMPファイルのパス\n"
		"    argv[3]: 出力ファイルの名前\n"
		"    実行時に，\n"
		"        ・分割するブロックのサイズ（int）\n"
		"        ・しきい値（double）\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：DCT係数\n"
		"               実際に出力されるファイルの名前は argv[3]-bxx_tyy.bmp，argv[3](dct)-bxx_tyy.txt です．\n"
		"               （ただし，xx:入力されたブロックのサイズ，yy:入力されたしきい値）\n"
		"\n"
		"  モード5: BMPを読み込み，圧縮します．\n"
		"    argv[1] = 5（モード指定引数）\n"
		"    argv[2]: 入力するBMPファイルのパス\n"
		"    argv[3]: 出力ファイルの名前\n"
		"    実行時に，\n"
		"        ・分割するブロックのサイズ（int）\n"
		"        ・しきい値（dobule）\n"
		"    を聞かれるので入力してください．\n"
		"    必要な結果：DCTの結果画像\n"
		"               実際に出力されるファイルの名前は argv[3]-bxx_tyy.bmp です．\n"
		"               （ただし，xx:入力されたブロックのサイズ，yy:入力されたしきい値）\n"
		"\n"
	);

	if ( argc != INPUT_FILE_NUM + 1 ) {
		printf("引数の数が違います．\n");
		exit( -1 );
	}

	if ( atoi( argv[1] ) == 0 ) {
		printf("\nモード%s...", argv[1]);
		a = loadFileAsArray_d( argv[2], false );
		a_out = dct_1d( a );
		printArray_dToFile( a_out, argv[3] );
		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi( argv[1] ) == 1 ) {
		printf("\nモード%s...", argv[1]);
		a = loadFileAsArray_d( argv[2], false );
		a_out = idct_1d( a );
		printArray_dToFile( a_out, argv[3] );
		freeArray_d( a );
		freeArray_d( a_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 2 ) {
		printf("\nモード%s...", argv[1]);
		m = loadFileAsMatrix( argv[2], false );
		m_out = dct_2d( m );
		printMatrixToFile( m_out, argv[3] );
		freeMatrix( m );
		freeMatrix( m_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 3 ) {
		printf("\nモード%s...", argv[1]);
		m = loadFileAsMatrix( argv[2], false );
		m_out = idct_2d( m );
		printMatrixToFile( m_out, argv[3] );
		freeMatrix( m );
		freeMatrix( m_out );
		printf("completed!\n");
		return 0;
	}

	if ( atoi(argv[1]) == 4 ) {
		printf("\nモード%s\n\n", argv[1]);
		b = loadFileAsBMP( argv[2], false );
		printBMPFileHeader( b.file_header );
		printBMPInfoHeader( b.info_header );
		printf("\n");
		threshold = getNum_double( "しきい値(小数値)" );
		block_size = getNum( "分割ブロックサイズ(整数値)" );
		sprintf( file_name, "%s(dct)-b%d_t%.1f.txt", argv[3], block_size, threshold );
		img = compressImage( b.img, threshold, block_size, true, file_name );
		freeBMP( b );
		b = newBMP( img );
		sprintf( file_name, "%s-b%d_t%.1f.bmp", argv[3], block_size, threshold );
		createBMPFile( b, file_name );
		freeBMP( b );
		printf("completed!\n");
		return 0;

	}

	if ( atoi(argv[1]) == 5 ) {
		printf("\nモード%s\n\n", argv[1]);
		b = loadFileAsBMP( argv[2], false );
		printBMPFileHeader( b.file_header );
		printBMPInfoHeader( b.info_header );
		printf("\n");
		threshold = getNum_double( "しきい値(小数値)" );
		block_size = getNum( "分割ブロックサイズ(整数値)" );
		img = compressImage( b.img, threshold, block_size, false, "" );
		freeBMP( b );
		b = newBMP( img );
		sprintf( file_name, "%s-b%d_t%.1f.bmp", argv[3], block_size, threshold );
		createBMPFile( b, file_name );
		freeBMP( b );
		printf("completed!\n");
		return 0;
	}

	printf("モードが正しく設定されていません．\n");
	return -1;
}



void FileOpenError( const char* file_name ) {
	printf("Could not Open \"%s\"\n", file_name );
	exit(-1);
}

void FileReadError( const char* value ) {
	printf( "Could not Read %s\n", value );
	exit( -1 );
}

void FileWriteError( const char* value ) {
	printf( "Could not Write %s\n", value );
	exit( -1 );
}

void AllocationError() {
	printf( "Allocation Error\n" );
	exit(-1);
}

void DataNumError() {
	printf("データ数が正しくありません．\n");
	exit(-1);
}



int countLinesOfFile( const char file_name[] ) {
	int num = 0;
	char line[24];

	FILE *fp = openFile( file_name, "r" );
	while( fgets( line , sizeof( line ) , fp ) != NULL ) {
		if ( line[0] == '\n' )
			continue;
		num++;
	}
	fclose( fp );

	return num;
}

void askForFilename( char file_name[] ) {
	printf("：");
	scanf( "%s", file_name );
}

int getNum( char description[] ) {
	int input;
	printf( "%s：", description );
	scanf( "%d", &input );
	return input;
}

double getNum_double( char description[] ) {
	double input;
	printf( "%s：", description );
	scanf( "%lf", &input );
	return input;
}

FILE* openFile( const char file_name[], const char* mode ) {
	FILE* file;

	if( ( file = fopen( file_name, mode ) ) == NULL )
		FileOpenError( file_name );

	return file;
}



Array_d* newArray_d( int length ) {
	Array_d *d;

	if( ( d = (Array_d*)malloc( sizeof( Array_d ) ) ) == NULL )
		AllocationError();

	if( ( d->a = (double*)malloc( sizeof(double) * length ) ) == NULL )
		AllocationError();

	d->length = length;

	return d;
}

void freeArray_d( Array_d* d ) {
	free( d->a );
	free( d );
}

Array_d* cloneArray_d( Array_d* vector, int dim ) {
	int i;

	Array_d* new_vector = newArray_d( dim );
	for ( i = 0; i < vector->length && i < new_vector->length; i++ ) {
		new_vector->a[i] = vector->a[i];
	}
	for ( ; i < new_vector->length; i++ ) {
		new_vector->a[i] = 0;
	}
	return new_vector;
}

Array_d* loadFileAsArray_d( const char file[], bool ask_filename ) {
	FILE *fp;
	Array_d *data;
	char file_name[FN]
	   , line[FN]
	;
	int length;

	if ( ask_filename ) {
		printf( "%s", file );
		askForFilename( file_name );
	}
	else
		strcpy( file_name, file );

	length = countLinesOfFile( file_name );
	data = newArray_d( length );

	fp = openFile( file_name, "r" );
	for ( int i = 0; i < data->length; ++i ) {
		fgets( line, sizeof(line), fp );
		sscanf( line , "%lf" , &data->a[i] );
	}
	fclose( fp );
	return data;
}

void printArray_d( Array_d* a ) {
	printf("length: %d\n", a->length);
	for ( int i = 0; i < a->length; i++ ) {
		printf("%f\n", a->a[i]);
	}
	printf("\n");
}

void printArray_dToFile( Array_d* d, const char file_name[] ) {
	FILE *fp = openFile( file_name, "w" );

	for ( int i = 0; i < d->length; ++i ) {
		fprintf( fp, "%f\n", d->a[i] );
	}

	fclose( fp );
}

Array_i* newArray_i( int length ) {
	Array_i *d;

	if( ( d = (Array_i*)malloc( sizeof( Array_i ) ) ) == NULL )
		AllocationError();

	if( ( d->a = (int*)malloc( sizeof(int) * length ) ) == NULL )
		AllocationError();

	d->length = length;

	return d;
}

void freeArray_i( Array_i* d ) {
	free( d->a );
	free( d );
}

Array_i* loadFileAsArray_i( const char file[], bool ask_filename ) {
	FILE *fp;
	Array_i *data;
	char file_name[FN]
	   , line[FN]
	;
	int length;

	if ( ask_filename ) {
		printf( "%s", file );
		askForFilename( file_name );
	}
	else
		strcpy( file_name, file );

	length = countLinesOfFile( file_name );
	data = newArray_i( length );

	fp = openFile( file_name, "r" );
	for ( int i = 0; i < data->length; ++i ) {
		fgets( line, sizeof(line), fp );
		sscanf( line , "%lf" , &data->a[i] );
	}
	fclose( fp );
	return data;
}

void printArray_i( Array_i* a ) {
	printf("length: %d\n", a->length);
	for ( int i = 0; i < a->length; i++ ) {
		printf("%d\n", a->a[i]);
	}
	printf("\n");
}

void printArray_iToFile( Array_i* d, const char file_name[] ) {
	FILE *fp = openFile( file_name, "w" );

	for ( int i = 0; i < d->length; ++i ) {
		fprintf( fp, "%d\n", d->a[i] );
	}

	fclose( fp );
}



Matrix* newMatrix( int row, int column ) {
	Matrix *d;

	if( ( d = (Matrix*)malloc( sizeof( Matrix ) ) ) == NULL )
		AllocationError();

	if( ( d->a = (double**)malloc( sizeof(double*) * row ) ) == NULL )
		AllocationError();

	for ( int i = 0; i < row; ++i ) {
		if( ( d->a[i] = (double*)malloc( sizeof(double) * column ) ) == NULL )
			AllocationError();
	}

	d->row = row;
	d->column = column;

	return d;
}

void freeMatrix( Matrix* d ) {
	for ( int i = 0; i < d->row; ++i ) {
		free( d->a[i] );
	}
	free( d->a );
	free( d );
}

Matrix *loadFileAsMatrix( const char file[], bool ask_filename ) {
	FILE *fp;
	Matrix *m;

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

	determineDimensionOfMatrix( file_name, &row, &column );
	m = newMatrix( row, column );

	fp = openFile( file_name, "r" );
	for ( int i = 0; i < row; i++ ) {
		if ( fgets( line, sizeof( line ) , fp ) == NULL )
			MatrixLoadError();

		m->a[i][0] = strtod( strtok( line, " " ), &ends );
		for ( int j = 1; j < column; j++ ) {
			m->a[i][j] = strtod( strtok( NULL, " " ), &ends );
		}
	}

	fclose( fp );
	return m;
}

void determineDimensionOfMatrix( const char file_name[], int* row, int* column ) {
	char line[FN];
	FILE *fp = openFile( file_name, "r" );

	if ( fgets( line, sizeof( line ) , fp ) == NULL )
		MatrixLoadError();

	*column = countSplitter( line, ' ' );
	*row = 1;

	while( fgets( line, sizeof( line ) , fp ) != NULL ) {
		if ( line[0] == '\n' )
			continue;
		(*row)++;
	}

	fclose( fp );
}

int countSplitter( const char* string, const char splitter ) {
	int i, count = 0;
	for ( i = 0; string[i] != '\0'; i++ ) {
		if ( string[i] == splitter )
			count++;
	}

	if ( string[i-1] == '\n' && string[i-2] == splitter )
		return count;

	if ( string[i-1] ==  splitter )
		return count;

	return count + 1;
}

void printMatrix( Matrix* a ) {
	printf("row: %d\n", a->row );
	printf("column: %d\n", a->column );

	for ( int i = 0; i < a->row; i++ ) {
		for ( int j = 0; j < a->column; j++ ) {
			printf( "%f ", a->a[i][j] );
		}
		printf("\n");
	}
	printf("\n");
}

void printMatrixToFile( Matrix* a, const char file_name[] ) {
	FILE *fp = openFile( file_name, "w" );

	for ( int i = 0; i < a->row; i++ ) {
		for ( int j = 0; j < a->column; j++ ) {
			fprintf( fp, "%f ", a->a[i][j] );
		}
		fprintf( fp, "\n" );
	}

	fclose( fp );
}

Matrix *multiply( Matrix *a, Matrix *b ) {
	Matrix *product;

	if ( a->column != b->row ) {
		InvalidMatrixFormatError();
		exit( -1 );
	}

	product = newMatrix( a->row, b->column );

	for ( int row = 0; row < a->row; row++ ) {
		for ( int col = 0; col < b->column; col++ ) {
			product->a[ row ][ col ] = 0;
			for ( int k = 0; k < a->column; k++ ) {
				product->a[ row ][ col ] += a->a[ row ][ k ] * b->a[ k ][ col ];
			}
		}
	}

	return product;
}

Matrix *transpose( Matrix* m ) {
	Matrix *transposed = newMatrix( m->column, m->row );

	for ( int row = 0; row < m->row; ++row ) {
		for ( int column = 0; column < m->column; ++column ) {
			transposed->a[ column ][ row ] = m->a[ row ][ column ];
		}
	}

	return transposed;
}


void MatrixLoadError() {
	printf( "Could not load as Matrix.\n" );
	exit( -1 );
}

void InvalidMatrixFormatError() {
	printf( "Invalid matrix format.\n" );
	exit( -1 );
}



void loadCharacters( FILE* fp, char* chars, int length ) {
	for ( int i = 0; i < length; i++ ) {
		if ( fread( &chars[i], sizeof( char ), 1, fp ) != 1 )
			FileReadError( "Characters" );
	}
}

long loadLongValue( FILE* fp ) {
	unsigned char s[4];
	if ( fread( s, 4, 1, fp ) != 1 )
		FileReadError( "Unsigned Long int" );
	if ( s[0] == 0 )
		return toUnsignedLong( s+1 );
	return toUnsignedLong( s+1 ) * -1;
}

long toLong( char s[] ) {
	return s[0] + 256 * ( s[1] + 256 * s[2] );
}

unsigned long loadUnsignedLongValue( FILE* fp ) {
	unsigned char s[4];
	if ( fread( s, 4, 1, fp ) != 1 )
		FileReadError( "Unsigned Long int" );
	return toUnsignedLong( s );
}

unsigned long toUnsignedLong( char s[] ) {
	return ( s[0] + 256 * ( s[1] + 256 * ( s[2] + 256 * s[3] ) ) );
}

short loadShortValue( FILE *fp ) {
	unsigned char s[2];
	if ( fread( s, 2, 1, fp ) != 1 )
		FileReadError( "Short int" );
	if ( s[0] == 0 )
		return s[1];
	return s[1] * -1;
}

unsigned short loadUnsignedShortValue( FILE* fp ) {
	unsigned char s[2];
	if ( fread( s, 2, 1, fp ) != 1 )
		FileReadError( "Unsigned Short int" );
	return toUnsignedShort( s );
}

unsigned short toUnsignedShort( char s[] ) {
	return ( s[0] + 256 * s[1] );
}

void writeCharacters( FILE* fp, const char* chars, int length ) {
	for ( int i = 0; i < length; i++ ) {
		if ( fwrite( &chars[i], sizeof( char ), 1, fp ) != 1 )
			FileWriteError( "Characters" );
	}
}

void writeLongValue( FILE* fp, unsigned long d ) {
	if ( fwrite( &d, 4, 1, fp ) != 1 )
		FileWriteError( "Long int" );
}

void writeShortValue( FILE* fp, unsigned short d ) {
	if ( fwrite( &d, 2, 1, fp ) != 1 )
		FileWriteError( "Short int" );
}



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



Array_d* dct_1d( Array_d* vector ) {
	return computeDCT_1d( vector, false );
}

Array_d* idct_1d( Array_d* vector ) {
	return computeDCT_1d( vector, true );
}

Array_d* computeDCT_1d( Array_d* vector, bool inverse ) {
	Array_d* transformed = newArray_d( vector->length );

	for( int k = 0; k < vector->length; ++k ) {
		transformed->a[k] = 0;

		for ( int n = 0; n < vector->length; ++n ) {
			if ( inverse ) {
				transformed->a[k] += vector->a[n] * generateDCTCoefficient( vector->length, k, n );
				continue;
			}
			transformed->a[k] += vector->a[n] * generateDCTCoefficient( vector->length, n, k );
		}
	}

	return transformed;
}

Matrix* dct_2d( Matrix* m ) {
	return computeDCT_2d( m, false );
}
Matrix* idct_2d( Matrix* m ) {
	return computeDCT_2d( m, true );
}

Matrix* computeDCT_2d( Matrix* m, bool inverse ) {
	Matrix *dct_matrix = generateDCTMatrix( m->row )
	     , *dct_matrix_transposed = transpose( dct_matrix )
	     , *forward, *dcted
	;

	if ( inverse ) {
		forward = multiply( dct_matrix_transposed, m );
		dcted = multiply( forward, dct_matrix );
	} else {
		forward = multiply( dct_matrix, m );
		dcted = multiply( forward, dct_matrix_transposed );
	}

	freeMatrix( forward );
	freeMatrix( dct_matrix );
	freeMatrix( dct_matrix_transposed );
	return dcted;
}

double generateDCTCoefficient( int dim, int n, int k ) {
	if ( k == 0 )
		return sqrt( 1.0/dim );
	return sqrt( 2.0/dim ) * cos( ( 2*n + 1 ) * k * M_PI / 2 / dim );
}

Matrix* generateDCTMatrix( int size ) {
	Matrix* dct_matrix = newMatrix( size, size );

	for ( int k = 0; k < size; ++k ) {
		for ( int n = 0; n < size; ++n ) {
			dct_matrix->a[ n ][ k ] = generateDCTCoefficient( size, k, n );
		}
	}

	return dct_matrix;
}



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
