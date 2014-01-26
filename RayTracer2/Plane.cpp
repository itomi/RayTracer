#include "Plane.h"


Plane::Plane(void) 
	:	m_normal(*new vect(1,0,0)),
		m_distance(0.0),
		m_color(*new Color(0.5,0.5,0.5, 0))
{}

Plane::Plane( vect& normal, double distance, Color& color) 
	:	m_normal(normal),
		m_distance(distance),
		m_color(color)
{}

Plane::Plane( const Plane& plane )
	: m_normal(*new vect(plane.m_normal)),
		m_distance(plane.m_distance),
		m_color(*new Color(plane.m_color))
{}


Plane::~Plane(void) {}

vect& Plane::getNormal() {
	return this->m_normal;
}

Color& Plane::getColor() {
	return m_color;
}

double& Plane::getDistance() {
	return m_distance;
}

double Plane::findIntersection( Ray& ray ) {
	vect& ray_distraction = ray.getDirection();
	double a = ray_distraction.dotProduct(m_normal);

	if( a == 0.0 ) {
		// promien jest rownolegly do podloza
		return -1;
	} else {
		double b = m_normal.dotProduct(ray.getOrigin().addVect(m_normal.multipVect(m_distance).negative()));
		return -1*b/a;
	}
}

vect Plane::getNormalAt( vect& vec2 ) {
	return m_normal;
}
