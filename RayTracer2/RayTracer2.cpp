// RayTracer2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX_LIGHTS 8
#define MAX_SPHERES 10
#define WINDOW_NAME "Raytracer"

typedef float point3[3];

int     imageSize = 400;
int		spheresCounter = 0;
int		lightsCounter = 0;

float   viewArea = 20.0;

float   light_position[MAX_LIGHTS][3];
float   light_specular[MAX_LIGHTS][3];
float   light_diffuse[MAX_LIGHTS][3];
float   light_ambient[MAX_LIGHTS][3];

float   sphere_radius[MAX_SPHERES];
float   sphere_position[MAX_SPHERES][3];
float   sphere_specular[MAX_SPHERES][3];
float   sphere_diffuse[MAX_SPHERES][3];
float   sphere_ambient[MAX_SPHERES][3];
float   sphere_specularhininess[MAX_SPHERES];

point3  backColor;
point3 globalLight;

void saveBMP(std::string fileName, int w, int h, int dpi, RGBColor *data) {
	std::fstream file;
	int dataLength = w*h;
	int fileSize = dataLength * 4;
	int wholeFileSize = 54 + fileSize;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int pixPerM = dpi*m;

	unsigned char bmpfileheader[14] = {'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };

	bmpfileheader[2] = (unsigned char) (wholeFileSize);
	bmpfileheader[3] = (unsigned char) (wholeFileSize>>8);
	bmpfileheader[4] = (unsigned char) (wholeFileSize>>16);
	bmpfileheader[5] = (unsigned char) (wholeFileSize>>24);

	bmpinfoheader[4] = (unsigned char) (w);
	bmpinfoheader[5] = (unsigned char) (w>>8);
	bmpinfoheader[6] = (unsigned char) (w>>16);
	bmpinfoheader[7] = (unsigned char) (w>>24);


	bmpinfoheader[8] = (unsigned char) (h);
	bmpinfoheader[9] = (unsigned char) (h>>8);
	bmpinfoheader[10] = (unsigned char) (h>>16);
	bmpinfoheader[11] = (unsigned char) (h>>24);

	bmpinfoheader[21] = (unsigned char) (fileSize);
	bmpinfoheader[22] = (unsigned char) (fileSize>>8);
	bmpinfoheader[23] = (unsigned char) (fileSize>>16);
	bmpinfoheader[24] = (unsigned char) (fileSize>>24);


	bmpinfoheader[25] = (unsigned char) (pixPerM);
	bmpinfoheader[26] = (unsigned char) (pixPerM>>8);
	bmpinfoheader[27] = (unsigned char) (pixPerM>>16);
	bmpinfoheader[28] = (unsigned char) (pixPerM>>24);


	bmpinfoheader[29] = (unsigned char) (pixPerM);
	bmpinfoheader[30] = (unsigned char) (pixPerM>>8);
	bmpinfoheader[31] = (unsigned char) (pixPerM>>16);
	bmpinfoheader[32] = (unsigned char) (pixPerM>>24);

	file.open(fileName, std::ios::out | std::ios::binary );

	file.write(reinterpret_cast<const char*>(bmpfileheader),14);
	file.write(reinterpret_cast<const char*>(bmpinfoheader),40);

	RGBColor rgb;
	for( int i = 0 ; i < dataLength ; i++ ) {
		rgb = data[i];

		double red = (data[i].r)*255;
		double green = (data[i].g)*255;
		double blue = (data[i].b)*255;

		unsigned char color[3]  = { (int)floor(blue), (int)floor(green), (int)floor(red) };
		file.write(reinterpret_cast<const char*>(color), 3);
	}

	file.flush();
	file.close();
}

int _tmain(int argc, char* argv[]) {
	std::string fileName = "";
	if( argc == 1 ) {
		std::cout<<"Podaj nazwe pliku: ";
		std::cin>>fileName;
	} else if( argc > 1 ) {
		fileName = std::string(argv[1]);
	}

	SettingsFile& fileWithSettings = SettingsFile::parseFile(fileName);
	std::cout<<"rendering..."<<std::endl;

	Command::CommandArgs& dimension = fileWithSettings.getArgsFor(Command::DIMENSION);

	int width = dimension.DimArgs.width;
	int hight  = dimension.DimArgs.hight;
	double aspectRatio = static_cast<double>(width) / static_cast<double>(hight);
	int arrayPoint = 0;

	RGBColor *pixel = new RGBColor[ width*hight ];
	vect O(0,0,0);
	vect x(1,0,0);
	vect y(0,1,0);
	vect z(0,0,1);

	vect campos(3.0,1.5,-4.0);
	vect look_at(0,0,0);
	vect diff_btw(campos.getX() - look_at.getX(), campos.getY() - look_at.getY(), campos.getZ() - look_at.getZ());

	vect camdir = vect::normalizeVect(diff_btw.negative());
	vect camright = vect::normalizeVect(y.crossProduct(camdir));
	vect camdown = camright.crossProduct(camdir);
	Camera scene_cam(campos, camdir, camright, camdown);

	Color white_light(1.0,1.0,1.0,0);
	Color pretty_green(0.5,1.0,0.5,0.3);
	Color maroon(0.5, 0.25, 0.25, 0.0);
	Color gray(0.5,0.5,0.5,0);
	Color black(0.0, 0.0,0.0, 0);

	Sphere scene_sphere(O, 1.0, pretty_green);
	Plane scene_plane(y, -1, maroon);
	std::vector<Object&> scene_objects;

	scene_objects.push_back(scene_plane);
	scene_objects.push_back(scene_sphere);

	double xamnt, yamnt; 

	for( int i = 0 ; i < width ; i++ ) {
		for( int j = 0 ; j < hight ; j++ ) {
			arrayPoint = j*width + i;

			if(width > hight) {
				xamnt = ((i+0.5)/width)*aspectRatio - (((width-hight)/(double)hight)/2.0);
				yamnt = ((hight - j) + 0.5)/hight;
			} else if( hight > width ) {
				xamnt = (i+0.5)/width; 
				yamnt = (((hight - j) + 0.5)/hight)/aspectRatio - (((hight - width)/(double)width)/2.0);
			} else {
				xamnt = (i + 0.5)/width;
				yamnt = ((hight - j) + 0.5)/hight;
			}

			vect cam_ray_origin = scene_cam.getCamPos();
			vect cam_ray_dir = camdir.addVect(camright.multipVect(xamnt - 0.5).addVect(camdown.multipVect(yamnt -0.5))).normalize();

			Ray cam_ray = Ray(cam_ray_origin, cam_ray_dir);

			std::vector<double> intersections;

		}
	}

	saveBMP(std::string("kul23132212.bmp"), width, hight, 72, pixel);

	system("pause");

	return 0;
}

