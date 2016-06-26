#ifndef IOF_H
#define IOF_H

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define FN 1024

int countLinesOfFile( const char file_name[] );
void askForFilename( char file_name[] );
int getNum( char description[] );
double getNum_double( char description[] );
FILE* openFile( const char file_name[], const char* mode );

#endif