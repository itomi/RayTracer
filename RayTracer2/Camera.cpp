#include "Camera.h"


Camera::Camera(void) 
	:	m_CameraPosition(*new vect(0.0,0.0,0.0)), 
		m_CameraDirection(*new vect(0.0,0.0,1.0)),
		m_CameraRight(*new vect(0.0,0.0,0.0)), 
		m_CameraDown(*new vect(0.0,0.0,0.0)) {}


Camera::~Camera(void){}

vect& Camera::getCamPos(){
	return this->m_CameraPosition;
}

vect& Camera::getCamDir(){
	return this->m_CameraDirection;
}

vect& Camera::getCamRight(){
	return this->m_CameraRight;
}

vect& Camera::getCamDown(){
	return this->m_CameraDown;
}
