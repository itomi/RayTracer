#pragma once
#include <cmath>
#include <iostream>

class vect
{
	double x,y,z;
public:
	vect(void);
	vect(const vect& vec);
	vect(double, double, double);
	~vect(void);

	double& getX();
	double& getY();
	double& getZ();

	double countMagnitude();

	void normalizeMe();
	vect negative();

	double dotProduct(vect& vec2);
	vect crossProduct(vect& vec2);
	vect addVect(vect& vec2);
	vect multipVect(double multiplier);

	static vect& normalizeVect(vect& vectToNormalize);
	static vect& negative(vect& vectToBeNegated);
	static double dotProduct(vect& vec1, vect& vec2);
	static vect& crossProduct(vect& vec1, vect& vec2);


	friend std::ostream& operator<<(std::ostream& os, const vect& obj) {
		os<<"vect [ "<<obj.x<<" ; "<<obj.y<<" ; "<<obj.z<<" ]";
		return os;
	}
};

