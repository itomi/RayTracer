#pragma once

#include "Object.h"

class Plane : public Object {
	vect& m_normal;
	double m_distance;
	Color& m_color;

public:
	Plane(void);
	Plane(const Plane& plane);
	Plane(vect&, double, Color&);
	~Plane(void);

	vect& getNormal();
	double& getDistance();
	virtual Color& getColor();
	virtual vect getNormalAt(vect& vec2);
	
	virtual double findIntersection(Ray& ray);
};

