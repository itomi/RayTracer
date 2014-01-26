#pragma once

#include "Ray.h"
#include "vect.h"
#include "Color.h"

class Object {
public:
	Object(void);
	~Object(void);

	Color& getObjectColor();

	double findIntersection(Ray& ray);
};
