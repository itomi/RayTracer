#include "Camera.h"


Camera::Camera(void) 
	:	m_CameraPosition(*new vect(0.0,0.0,0.0)), 
		m_CameraDirection(*new vect(0.0,0.0,1.0)),
		m_CameraRight(*new vect(0.0,0.0,0.0)), 
		m_CameraDown(*new vect(0.0,0.0,0.0)) {}

Camera::Camera( vect& pos, vect& dir, vect& right, vect& down )
	:	m_CameraPosition(pos),
		m_CameraDirection(dir),
		m_CameraRight(right),
		m_CameraDown(down)
{}

Camera::Camera( const Camera& camera )
	:	m_CameraPosition(*new vect(camera.m_CameraPosition)),
		m_CameraDirection(*new vect(camera.m_CameraDirection)),
		m_CameraRight(*new vect(camera.m_CameraRight)),
		m_CameraDown(*new vect(camera.m_CameraDown))
{}


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
