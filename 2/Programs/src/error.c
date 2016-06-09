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