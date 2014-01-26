#include "Sphere.h"


Sphere::Sphere(void) 
	:	position(*new vect(0.0,0.0,0.0)),
		radius(1.0),
		color(*new Color(0.5,0.5,0.5,0.0))
{}

Sphere::Sphere( const Sphere& sphere ) 
	:	position(*new vect(sphere.position)),
		radius(sphere.radius),
		color(*new Color(sphere.color))
{}

Sphere::Sphere( vect& position, double radius, Color& color) 
	:	position(position),
		radius(radius),
		color(color)
{}

Sphere::~Sphere(void) {}

double& Sphere::getRadius() {
	return radius;
}

vect& Sphere::getPosition() {
	return position;
}

Color& Sphere::getColor() {
	return color;
}

vect Sphere::getNormalAt( vect& point ) {
	return point.addVect(position.negative()).normalize();
}

double Sphere::findIntersection( Ray& ray ) {
	vect& ray_origin = ray.getOrigin();
	double ray_origin_x = ray_origin.getX();
	double ray_origin_y = ray_origin.getY();
	double ray_origin_z = ray_origin.getZ();

	vect& ray_direction = ray.getDirection();
	double ray_dir_x = ray_direction.getX();
	double ray_dir_y = ray_direction.getY();
	double ray_dir_z = ray_direction.getZ();

	double sphere_x = position.getX();
	double sphere_y = position.getY();
	double sphere_z = position.getZ();

	double a = 1.0;
	double b = (2.0 * (ray_origin_x - sphere_x) * ray_dir_x) + (2.0 * (ray_origin_y - sphere_y) * ray_dir_y) + (2.0 * (ray_origin_z - sphere_z) * ray_dir_z);
	double c = pow(ray_origin_x - sphere_x, 2) + pow(ray_origin_y - sphere_y, 2) + pow(ray_origin_z - sphere_z, 2) - (radius*radius);

	double discriminant = b*b - 4*c;

	if( discriminant > 0.0 ) {
		double hit1 = ((-1.0*b - sqrt(discriminant))/2.0) - 0.000001;
		if( hit1 > 0.0 ) {
			return hit1;
		} else {
			return ((sqrt(discriminant) - b)/2.0) -  0.000001;
		}
	} else {
		return -1.0;
	}
}
