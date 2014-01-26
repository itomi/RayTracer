#pragma once

#include "vect.h"

class Camera
{
	vect& m_CameraPosition, m_CameraDirection, m_CameraRight, m_CameraDown;

public:
	Camera(void);
	~Camera(void);

	vect& getCamPos();
	vect& getCamDir();
	vect& getCamRight();
	vect& getCamDown();

};

