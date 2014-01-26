#pragma once

#include "Source.h"
#include "vect.h"
#include "Color.h"

class Light : public Source {
	vect& m_pos;
	Color& m_lightColor;
public:
	Light(void);
	Light(vect&, Color&);
	Light(const Light& light);
	~Light(void);

	virtual vect& getPosition();
	virtual Color& getColor();
};

