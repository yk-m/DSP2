#include "complex.h"

complex_t addComplex( complex_t a, complex_t b )
{
	complex_t sum;

	sum.re = a.re + b.re;
	sum.im = a.im + b.im;

	return sum;
}

complex_t subtractComplex( complex_t minuend, complex_t subtrahend )
{
	complex_t difference;

	difference.re = minuend.re - subtrahend.re;
	difference.im = minuend.im - subtrahend.im;

	return difference;
}

complex_t multiplyComplex( complex_t a, complex_t b )
{
	complex_t product;

	product.re = a.re * b.re - a.im * b.im;
	product.im = a.im * b.re + a.re * b.im;

	return product;
}

complex_t divideComplex( complex_t dividend, complex_t divisor )
{
	complex_t quotient;

	quotient.re = ( dividend.re * divisor.re + dividend.im * divisor.im ) / ( pow ( divisor.re, 2 ) + pow ( divisor.im, 2 ) );
	quotient.im = ( dividend.im * divisor.re - dividend.re * divisor.im ) / ( pow ( divisor.re, 2 ) + pow ( divisor.im, 2 ) );

	return quotient;
}

complex_t conjugateComplex( complex_t c )
{
	c.im *= -1;
	return c;
}

double calcRadius( complex_t c )
{
	return sqrt( pow( c.re, 2 ) + pow( c.im, 2 ) );
}

double calcAngle( complex_t c )
{
	return atan2( c.im, c.re );
}

polar_t convertRectangularToPolar( complex_t c )
{
	polar_t p;

	p.radius = calcRadius( c );
	p.angle = calcAngle( c );

	return p;
}

complex_t convertPolarToRectangular( polar_t p )
{
	complex_t c;

	c.re = p.radius * ( cos( p.angle ) );
	c.im = p.radius * ( sin( p.angle ) );

	return c;
}

complex_t generateTwiddleFactor( int dimension, int nth )
{
	polar_t p = { 1, -2.0 * M_PI * nth / dimension };
	return convertPolarToRectangular( p );
}
