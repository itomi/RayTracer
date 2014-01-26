#include "Color.h"


Color::Color(void) 
	:	r(0),
		g(0),
		b(0),
		special(0)
{}

Color::Color( double red ,double green,double blue,double spec)
	:	r(red),
		g(green),
		b(blue),
		special(spec)
{}

Color::Color( const Color& color ) 
	:	r(color.r),
		g(color.g),
		b(color.b),
		special(color.special)
{}

Color::~Color(void)
{
}

double& Color::getR() {
	return r;
}

double& Color::getG() {
	return g;
}

double& Color::getB() {
	return b;
}

void Color::setR( double r ) {
	this->r = r;
}
void Color::setG( double g ) {
	this->g = g;
}
void Color::setB( double b ) {
	this->b = b;
}
