#include "Ray.h"


Ray::Ray(void) : origin(*new vect()), direction(*new vect(1.0,0.0,0.0)) { }

Ray::Ray( vect& origin, vect& direction ): origin(origin), direction(direction) { }


Ray::~Ray(void)
{
}
