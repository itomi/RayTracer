#pragma once

#include "vect.h"

class Ray
{
	vect& origin, direction;

public:
	Ray(void);
	Ray(vect& origin, vect& direction);
	~Ray(void);

	vect& getOrigin();
	vect& getDirection();
	
};

