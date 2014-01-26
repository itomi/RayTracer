#include "vect.h"


vect::vect(void) : x(0.0), y(0.0), z(0.0) {}

vect::vect( double x, double y , double z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}


vect::~vect(void)
{
}

double& vect::getX() {
	return this->x;
}

double& vect::getY() {
	return this->y;
}

double& vect::getZ() {
	return this->z;
}

vect& vect::normalizeVect( vect& vectToNormalize ) {

	double& x = vectToNormalize.getX();
	double& y = vectToNormalize.getY();
	double& z = vectToNormalize.getZ();

	double magnitude = sqrt(x*x + y*y + z*z);
	return (magnitude > 0.0 ? *new vect(x / magnitude, y / magnitude, z / magnitude) : *new vect(0.0,0.0,0.0));
}

void vect::normalizeMe() {
	double fm_magnitude = sqrt(x*x + y*y + z*z);
	if( fm_magnitude > 0.0 ) {
		this->x = x / fm_magnitude;
		this->y = y / fm_magnitude;
		this->z = z / fm_magnitude;
	}
}
