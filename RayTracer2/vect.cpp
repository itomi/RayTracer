#include "vect.h"


vect::vect(void) : x(0.0), y(0.0), z(0.0) {}

vect::vect( double x, double y , double z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vect::vect( const vect& vec ) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
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

vect vect::normalize() {
	double fm_magnitude = sqrt(x*x + y*y + z*z);
	if( fm_magnitude > 0.0 ) {
		return vect(x / fm_magnitude, y / fm_magnitude,z / fm_magnitude);
	}
	return vect(0.0,0.0,0.0);
}

vect& vect::negative( vect& vectToBeNegated ) {
	return *new vect(-vectToBeNegated.x,-vectToBeNegated.y,-vectToBeNegated.z);
}

vect vect::negative() {
	return vect(-x,-y,-z);
}

double vect::dotProduct( vect& vec2 ) {
	return x*vec2.x + y*vec2.y + z*vec2.z;
}

double vect::dotProduct( vect& vec1, vect& vec2 ) {
	return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

vect vect::crossProduct( vect& vec2 ) {
	return vect(y*vec2.z - z*vec2.y, z*vec2.x - x*vec2.z, x*vec2.y - y*vec2.x);
}

vect& vect::crossProduct( vect& vec1, vect& vec2 ) {
	return *new vect(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}

vect vect::addVect( vect& vec2 ){
	return vect(x+vec2.x, y+vec2.y, z+vec2.z);
}

vect vect::multipVect( double multiplier ) {
	return vect(x*multiplier,y*multiplier,z*multiplier);
}

double vect::countMagnitude() {
	return sqrt(x*x+y*y+z*z);
}
