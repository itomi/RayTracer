#pragma once
#include <cmath>
#include <iostream>

class vect
{
	double x,y,z;
public:
	vect(void);
	vect(double, double, double);
	~vect(void);

	double& getX();
	double& getY();
	double& getZ();

	
	void normalizeMe();
	static vect& normalizeVect(vect& vectToNormalize);

	friend std::ostream& operator<<(std::ostream& os, const vect& obj) {
		os<<"vect [ "<<obj.x<<" ; "<<obj.y<<" ; "<<obj.z<<" ]";
		return os;
	}
};

