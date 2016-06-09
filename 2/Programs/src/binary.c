#include "binary.h"

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
