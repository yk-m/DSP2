#include "jacobi.h"

Array_Eigen* jacobi( Matrix *m, double gap ) {
	Matrix *eigen_values = m
	     , *eigen_vectors = newIdentityMatrix( m->row, m->row )
	;
	Coordinate position;
	Trigonometry angle;
	Array_Eigen *result;

	int count = 0
	  , not_change = 0
	;
	double previous = 0;

	while(1) {
		position = locateMaxValue( eigen_values );
		if ( position.value < gap )
			break;

		if ( position.value == previous )
			not_change++;
		else
			not_change = 0;

		if ( not_change == 100 )
			break;

		previous = position.value;

		angle = calcAngle( m, position );
		rotate( eigen_values,  position, angle );
		append( eigen_vectors, position, angle );
		repair( eigen_values );
	}

	result = splitToEigen( eigen_values, eigen_vectors );
	sort( result );
	return result;
}

Array_Eigen* splitToEigen( Matrix *eigen_values, Matrix *eigen_vectors ) {
	Array_Eigen* r = newArray_Eigen( eigen_values->column );

	for ( int col = 0; col < eigen_values->column; col++ ) {
		r->a[col] = newEigen();
		r->a[col]->vector = newMatrix( eigen_vectors->row, 1 );
		r->a[col]->value = eigen_values->a[col][col];
		for ( int row = 0; row < r->a[col]->vector->row; row++ ) {
			r->a[col]->vector->a[row][0] = eigen_vectors->a[row][col];
		}
	}

	return r;
}

void sort( Array_Eigen* eigens ) {
	Eigen* tmp;
	for ( int i = 0; i < eigens->length; i++ ) {
		for ( int j = eigens->length - 1; j > i ; j-- ) {
			if ( eigens->a[j]->value <= eigens->a[j-1]->value )
				continue;
			tmp = eigens->a[j];
			eigens->a[j] = eigens->a[j-1];
			eigens->a[j-1] = tmp;
		}
	}
}

// void sort( Matrix *m ) {
// 	double *tmp;
// 	for ( int i = 0; i < m->row; i++ ) {
// 		for ( int j = m->row - 1; j > i; j-- ) {
// 			if ( m->a[j][0] <= m->a[j-1][0] )
// 				continue;
// 			tmp = m->a[j];
// 			m->a[j] = m->a[j-1];
// 			m->a[j-1] = tmp;
// 		}
// 	}
// }

void rotate( Matrix *m, Coordinate position, Trigonometry angle ) {
	double tmp_i, tmp_j
	     , mii = m->a[ position.i ][ position.i ]
	     , mij = m->a[ position.i ][ position.j ]
	     , mjj = m->a[ position.j ][ position.j ]
	     , sin_pow2  = angle.sin * angle.sin
	     , cos_pow2  = angle.cos * angle.cos
	     , sin_x_cos = angle.sin * angle.cos
	;

	// P^-1 * A
	for ( int i = 0; i < m->row; i++ ) {
		tmp_i = m->a[ position.i ][i];
		tmp_j = m->a[ position.j ][i];
		m->a[ position.i ][i] = angle.cos * tmp_i - angle.sin * tmp_j;
		m->a[ position.j ][i] = angle.sin * tmp_i + angle.cos * tmp_j;
	}

	// A * P
	for ( int i = 0; i < m->row; i++ ) {
		m->a[i][ position.i ] = m->a[ position.i ][i];
		m->a[i][ position.j ] = m->a[ position.j ][i];
	}

	// 重複部分
	m->a[ position.i ][ position.i ] = cos_pow2 * mii + sin_pow2 * mjj - 2 * sin_x_cos * mij;
	m->a[ position.j ][ position.j ] = sin_pow2 * mii + cos_pow2 * mjj + 2 * sin_x_cos * mij;

	m->a[ position.i ][ position.j ] = sin_x_cos * ( mii - mjj ) + ( cos_pow2 - sin_pow2 ) * mij;
	m->a[ position.j ][ position.i ] = m->a[ position.i ][ position.j ];
}

void append( Matrix *m, Coordinate position, Trigonometry angle ) {
	double tmp_i, tmp_j
	     , mii = m->a[ position.i ][ position.i ]
	     , mij = m->a[ position.i ][ position.j ]
	     , mjj = m->a[ position.j ][ position.j ]
	;

	for ( int i = 0; i < m->row; i++ ) {
		tmp_i = m->a[i][ position.i ];
		tmp_j = m->a[i][ position.j ];
		m->a[i][ position.i ] = angle.cos * tmp_i - angle.sin * tmp_j;
		m->a[i][ position.j ] = angle.sin * tmp_i + angle.cos * tmp_j;
	}
}

Trigonometry calcAngle( Matrix *m, Coordinate position ) {
	double mii = m->a[ position.i ][ position.i ]
	     , mij = m->a[ position.i ][ position.j ]
	     , mjj = m->a[ position.j ][ position.j ]
	;
	Trigonometry angle;

	double alpha = ( mii - mjj ) / 2
	     , beta  = -mij
	     , gamma = fabs( alpha ) / sqrt( alpha * alpha + beta * beta )
	;

	angle.sin = sqrt( ( 1 - gamma ) / 2 );
	angle.cos = sqrt( ( 1 + gamma ) / 2 );

	if( alpha * beta < 0 )
		angle.sin *= -1;

	return angle;
}

Coordinate locateMaxValue( Matrix *m ) {
	Coordinate position = { 0, 0, -1 };

	for ( int i = 0; i < m->row; i++ ) {
		for ( int j = i+1; j < m->column; j++ ) {
			if ( fabs( m->a[i][j] ) <= position.value )
				continue;
			position.i = i;
			position.j = j;
			position.value = fabs( m->a[i][j] );
		}
	}
	return position;
}

void repair( Matrix *matrix ) {
	for ( int i = 0; i < matrix->row; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			matrix->a[j][i] = matrix->a[i][j];
		}
	}
}