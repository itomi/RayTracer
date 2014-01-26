#include "Object.h"


Object::Object(void) {}


Object::~Object(void) {}

Color& Object::getColor() {
	return *new Color(0.0,0.0,0.0,0.0);
}

double Object::findIntersection( Ray& ray ) {
	return 0.0;
}
