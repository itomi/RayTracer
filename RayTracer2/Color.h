#pragma once
class Color {
	double r,g,b, special;
public:
	Color(void);
	Color(double,double,double,double);
	Color(const Color& color);
	~Color(void);

	double& getR();
	double& getG();
	double& getB();
	double& getS();

	void setR(double r);
	void setG(double g);
	void setB(double b);
	void setS(double s);

	double getBrightness();

	Color colorScalar(double scalar);
	Color addColor(Color& color);
	Color colorMultiply(Color& color);
	Color colorAverage(Color& color);
};

