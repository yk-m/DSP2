#include "iof.h"

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
