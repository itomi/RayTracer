#pragma once

#include <cmath>
#include "Object.h"
#include "Color.h"
#include "vect.h"

class Sphere : public Object {
	vect& position;
	double radius;
	Color& color;

public:
	Sphere(void);
	Sphere(const Sphere& sphere);
	Sphere(vect&, double, Color&);
	~Sphere(void);

	double& getRadius();
	vect& getPosition();
	Color& getColor();
};

