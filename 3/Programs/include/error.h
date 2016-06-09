#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

void FileOpenError( const char* file_name );
void FileReadError( const char* value );
void FileWriteError( const char* value );
void AllocationError();
void DataNumError();

#endif