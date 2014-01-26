#include "Light.h"


Light::Light(void)
	:	m_pos(*new vect(0.0,0.0,0.0)),
		m_lightColor(*new Color(1,1,1,0)) 
{}

Light::Light( vect& position, Color& lightCol ) 
	:	m_pos(position),
		m_lightColor(lightCol)
{}

Light::Light( const Light& light )
	:	m_pos(*new vect(light.m_pos)),
		m_lightColor(*new Color(light.m_lightColor)) 
{}


Light::~Light(void) {}

vect& Light::getPosition() {
	return m_pos;
}

Color& Light::getColor() {
	return m_lightColor;
}
