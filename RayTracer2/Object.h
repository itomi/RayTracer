#pragma once

#include "Ray.h"
#include "vect.h"
#include "Color.h"

class Object {
public:
	Object(void);
	~Object(void);

	virtual Color& getColor();
	virtual double findIntersection(Ray& ray);
	virtual vect getNormalAt(vect& vec2) = 0;
}; 
