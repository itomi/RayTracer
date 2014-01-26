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

double Color::getBrightness() {
	return (r+b+g)/3.0;
}

Color Color::colorScalar( double scalar ){
	return Color(scalar * r, scalar * g, scalar * b, special );
}

Color Color::addColor( Color& color ) {
	return Color(r + color.r, g + color.g, b + color.b, special);
}

Color Color::colorMultiply( Color& color ) {
	return Color(r*color.r, g*color.g, b*color.b, special);
}

Color Color::colorAverage( Color& color ) {
	return Color((r*color.r)/2.0, (g*color.g)/2.0, (b*color.b)/2.0, special);
}
