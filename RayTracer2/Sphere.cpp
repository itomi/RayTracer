#include "Sphere.h"


Sphere::Sphere(void) 
	:	position(*new vect(0.0,0.0,0.0)),
		radius(1.0),
		color(*new Color(0.5,0.5,0.5,0.0))
{}

Sphere::Sphere( const Sphere& sphere ) 
	:	position(*new vect(sphere.position)),
		radius(sphere.radius),
		color(*new Color(sphere.color))
{}

Sphere::Sphere( vect& position, double radius, Color& color) 
	:	position(position),
		radius(radius),
		color(color)
{}

Sphere::~Sphere(void) {}

double& Sphere::getRadius() {
	return radius;
}

vect& Sphere::getPosition() {
	return position;
}

Color& Sphere::getColor() {
	return color;
}