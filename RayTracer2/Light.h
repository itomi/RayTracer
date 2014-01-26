#pragma once

#include "vect.h"
#include "Color.h"

class Light
{
	vect& m_pos;
	Color& m_lightColor;
public:
	Light(void);
	Light(vect&, Color&);
	Light(const Light& light);
	~Light(void);
};

