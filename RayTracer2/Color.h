//#pragma once
//class Color {
//	double r,g,b, special;
//public:
//	Color(void);
//	Color(double,double,double,double);
//	Color(const Color& color);
//	~Color(void);
//
//	double& getR();
//	double& getG();
//	double& getB();
//	double& getS();
//
//	void setR(double r);
//	void setG(double g);
//	void setB(double b);
//	void setS(double s);
//
//	double getBrightness();
//
//	Color colorScalar(double scalar);
//	Color addColor(Color& color);
//	Color colorMultiply(Color& color);
//	Color colorAverage(Color& color);
//	Color clip();
//};

#pragma once
class Color {
	double red, green, blue, special;

public:

	Color ();

	Color (double, double, double, double);

	// method functions
	double getR() { return red; }
	double getG() { return green; }
	double getB() { return blue; }
	double getS() { return special; }

	double setR(double redValue) { red = redValue; return red; }
	double setG(double greenValue) { green = greenValue; return green; }
	double setB(double blueValue) { blue = blueValue; return blue; }
	double setS(double specialValue) { special = specialValue; return special; }

	double brightness() {
		return(red + green + blue)/3;
	}

	Color colorScalar(double scalar) {
		return Color (red*scalar, green*scalar, blue*scalar, special);
	}

	Color addColor(Color color) {
		return Color (red + color.getR(), green + color.getG(), blue + color.getB(), special);
	}

	Color colorMultiply(Color color) {
		return Color (red*color.getR(), green*color.getG(), blue*color.getB(), special);
	}

	Color colorAverage(Color color) {
		return Color ((red + color.getR())/2, (green + color.getG())/2, (blue + color.getB())/2, special);
	}

	Color clip() {
		double alllight = red + green + blue;
		double excesslight = alllight - 3;
		if (excesslight > 0) {
			red = red + excesslight*(red/alllight);
			green = green + excesslight*(green/alllight);
			blue = blue + excesslight*(blue/alllight);
		}
		if (red > 1) {red = 1;}
		if (green > 1) {green = 1;}
		if (blue > 1) {blue = 1;}
		if (red < 0) {red = 0;}
		if (green < 0) {green = 0;}
		if (blue < 0) {blue = 0;}

		return Color (red, green, blue, special);
	}
};