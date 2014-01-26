#pragma once

#include "vect.h"
#include "Color.h"

class Source
{
public:
	Source(void);
	Source(const Source& source);
	~Source(void);

	virtual vect& getPosition() = 0;
	virtual Color& getColor() = 0;
};

