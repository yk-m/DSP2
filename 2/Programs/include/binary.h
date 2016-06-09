#ifndef BINARY_H
#define BINARY_H

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

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

#endif