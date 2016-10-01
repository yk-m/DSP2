#include "matrix.h"

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

Matrix* newIdentityMatrix( int row, int column ) {
	Matrix *d = newMatrix( row, column );

	for ( int r = 0; r < d->row; ++r ) {
		for ( int c = 0; c < d->column; ++c ) {
			if ( r == c ) {
				d->a[r][c] = 1;
				continue;
			}
			d->a[r][c] = 0;
		}
	}

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
	   , line[LINE_MAX]
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

Matrix *cloneMatrix( Matrix* m ) {
	Matrix* clone = newMatrix( m->row, m->column );

	for ( int r = 0; r < clone->row; ++r ) {
		for ( int c = 0; c < clone->column; ++c ) {
			clone->a[r][c] = m->a[r][c];
		}
	}

	return clone;
}

void determineDimensionOfMatrix( const char file_name[], int* row, int* column ) {
	char line[LINE_MAX];
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

Matrix *subtract( Matrix *a, Matrix *b ) {
	Matrix *diff;

	if ( a->row != b->row || a->column != b->column ) {
		InvalidMatrixFormatError();
	}

	diff = newMatrix( a->row, a->column );

	for ( int row = 0; row < a->row; row++ ) {
		for ( int col = 0; col < b->column; col++ ) {
			diff->a[ row ][ col ] = a->a[ row ][ col ] - b->a[ row ][ col ];
		}
	}

	return diff;
}

Matrix *multiply( Matrix *a, Matrix *b ) {
	Matrix *product;

	if ( a->column != b->row ) {
		InvalidMatrixFormatError();
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

Matrix *multiplyByScalar( Matrix *a, double b )  {
	 Matrix *product = newMatrix( a->row, a->column );
	for ( int row = 0; row < a->row; row++ ) {
		for ( int column = 0; column < a->column; ++column ) {
			product->a[row][column] = a->a[row][column] * b;
		}
	}

	return product;
}

Matrix *divideByScalar( Matrix *a, double b ) {
	 Matrix *quotient = newMatrix( a->row, a->column );
	for ( int row = 0; row < a->row; row++ ) {
		for ( int column = 0; column < a->column; ++column ) {
			quotient->a[row][column] = a->a[row][column] / b;
		}
	}

	return quotient;
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

double dotProduct( Matrix* a, Matrix* b ) {
	double product = 0;

	if ( a->column != 1 || b->column != 1 || a->row != b->row ) {
		InvalidMatrixFormatError();
	}

	for ( int row = 0; row < a->row; ++row ) {
		product += a->a[row][0] * b->a[row][0];
	}
	return product;
}

double calcNorm( Matrix* a ) {
	return sqrt( dotProduct( a, a ) );
}


void MatrixLoadError() {
	printf( "Could not load as Matrix.\n" );
	exit( -1 );
}

void InvalidMatrixFormatError() {
	printf( "Invalid matrix format.\n" );
	exit( -1 );
}
