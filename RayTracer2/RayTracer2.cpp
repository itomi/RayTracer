// RayTracer2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void createSpheres(std::vector<Object*> scene_objs, SettingsFile& file) {
	std::vector<Command::CommandArgs> spheres = file.getArgsFor(Command::SPHERE);

	for( Command::CommandArgs arg : spheres ) {
		std::cout<<arg.SphereArgs.xpos<<" - "<<arg.SphereArgs.ypos<<std::endl;
		scene_objs.push_back(new Sphere(*new vect(arg.SphereArgs.xpos, arg.SphereArgs.ypos, arg.SphereArgs.zpos), arg.SphereArgs.radius, *new Color(arg.SphereArgs.specular[0],arg.SphereArgs.specular[1],arg.SphereArgs.specular[2], ((double)arg.SphereArgs.shinines)/100.0)));
	}
}

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

Color getColorAt(vect& intersection_pos, vect& intersection_ray_dir, std::vector<Object*>& scene_objs, int index_of_intersection, std::vector<Source*>& lightSources, double accuracy, double ambLight ) {
	
	Color& first_obj_color = scene_objs.at(index_of_intersection)->getColor();
	vect& first_obj_normal = scene_objs.at(index_of_intersection)->getNormalAt(intersection_pos);
	Color&  finalColor = first_obj_color.colorScalar(ambLight);
	for(int l = 0 ; l < lightSources.size() ; l++ ) {
		Source* light = lightSources.at(l);
		vect& light_dir = vect(light->getPosition().addVect(intersection_pos.negative()).normalize());

		float cosine_angle = first_obj_normal.dotProduct(light_dir);

		if( cosine_angle > 0.0 ) { // cien jest
			bool shadow = false;
			vect& distanceToLight = light->getPosition().addVect(intersection_pos.negative()).normalize();
			float distanceToLightMagnitude = distanceToLight.countMagnitude();

			Ray& shadow_ray = Ray(intersection_pos, light->getPosition().addVect(intersection_pos.negative()).normalize());

			std::vector<double> secondary_intersection;
			if( shadow ) {
				for( int i = 0 ; i < scene_objs.size() ; i++) {
					Object* obj = scene_objs.at(i);
					secondary_intersection.push_back(obj->findIntersection(shadow_ray));
				}	
				for( int i = 0 ; i < secondary_intersection.size() ; i++ ) {
					double intersect_value = secondary_intersection.at(i);
					if( intersect_value > accuracy ) {
						if( intersect_value <= distanceToLightMagnitude )
							shadow = true;
					}
					
					break;
				}
			} 

			if( shadow == false ) {
				finalColor = finalColor.addColor(first_obj_color.colorMultiply(light->getColor()).colorScalar(cosine_angle));

				if( first_obj_color.getS() > 0.0 && first_obj_color.getS() <= 1.0 ) {
					double val = first_obj_normal.dotProduct(intersection_ray_dir.negative());
					vect& scalar = first_obj_normal.multipVect(val);
					vect& additive = scalar.addVect(intersection_ray_dir);
					vect& scalar2 = additive.multipVect(2.0);
					vect& aditive2 = intersection_ray_dir.negative().addVect(scalar2);
					vect& reflection_dir = aditive2.normalize();

					double specular = reflection_dir.dotProduct(light_dir);
					if(specular > 0.0) {
						specular = pow(specular,10);
						finalColor = finalColor.addColor((light->getColor().colorScalar(specular*first_obj_color.getS())));
					}

				}

			}
		}
	}

	return finalColor.clip();
}

int firstIntersection(std::vector<double>& intersections ) {
	switch(intersections.size()) {
	case 0:
		return -1;
		break;
	case 1:
		return (intersections.at(0) > 0.0 ? 0 : -1);
		break;
	default:
		double max = 0.0;
		for( int i = 0 ; i < intersections.size() ; i++ ) {
			if( max < intersections.at(i) ) {
				max = intersections.at(i);
			}
		}

		if( max > 0.0 ) {
			int index;
			for( int i = 0 ; i < intersections.size() ; i++ ) {
				double intersec = intersections.at(i);
				if(  intersec > 0.0 && intersec <= max ) {
					max = intersec;
					index = i;
				}
			}
			return index;
		} else {
			return -1;
		}
	}
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

	fileWithSettings.printCommands(std::cout);

	std::cout<<"rendering..."<<std::endl;

	std::vector<Command::CommandArgs> dimension = fileWithSettings.getArgsFor(Command::DIMENSION);

	int width = dimension.at(0).DimArgs.width;
	int hight  = dimension.at(0).DimArgs.hight;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   
	glutInitWindowSize(width, hight);
	glutCreateWindow("Ray Tracing");

	double aspectRatio = static_cast<double>(width) / static_cast<double>(hight);
	double ambLight = 0.5;
	double accuracy = 0.000001;

	int arrayPoint = 0;

	RGBColor *pixel = new RGBColor[ width*hight ];
	GLubyte  glpixel[1][1][3];
	vect O(0,0,0);
	vect x(1,0,0);
	vect y(0,1,0);
	vect planePos(0,-2.0,0);
	vect z(0,0,1);

	vect camPosition(3.0,1.5,-10.0);
	vect camLookAt(0,0,0);
	vect camPointsOnVec(camPosition.getX() - camLookAt.getX(), camPosition.getY() - camLookAt.getY(), camPosition.getZ() - camLookAt.getZ());

	vect cameraDir = vect::normalizeVect(camPointsOnVec.negative());
	vect camright = vect::normalizeVect(y.crossProduct(cameraDir));
	vect camdown = camright.crossProduct(cameraDir);
	Camera scene_cam(camPosition, cameraDir, camright, camdown);

	Color white_light (1.0, 1.0, 1.0, 0);
	Color pretty_green (0.5, 1.0, 0.5, 1.0);
	Color maroon (0.5, 0.25, 0.25, 0);
	Color tile_floor (1, 1, 1, 2);
	Color gray (0.5, 0.5, 0.5, 0);
	Color black (0.0, 0.0, 0.0, 0);

	Sphere scene_sphere(O, 1.0, pretty_green);
	Plane scene_plane(y, -1, maroon);
	vect& light_pos = vect(-7,10, -10);
	Light scene_light(light_pos, white_light);
	Light ambient_light(light_pos, white_light);

	std::vector<Object*> scene_objects;
	std::vector<Source*> scene_lights;

	createSpheres(scene_objects, fileWithSettings);

	scene_lights.push_back(dynamic_cast<Source*>(&scene_light));
	//scene_lights.push_back(dynamic_cast<Source*>(&ambient_light));

	scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));
	scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));

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
			vect cam_ray_dir = cameraDir.addVect(camright.multipVect(xamnt - 0.5).addVect(camdown.multipVect(yamnt -0.5))).normalize();

			Ray cam_ray = Ray(cam_ray_origin, cam_ray_dir);

			std::vector<double> intersections;

			for( Object* obj : scene_objects ) {
				intersections.push_back(obj->findIntersection(cam_ray));
			}

			int index_of_first_intersection = firstIntersection(intersections);

			if(index_of_first_intersection == -1) {
				pixel[arrayPoint].r = 0;
				pixel[arrayPoint].b = 0;
				pixel[arrayPoint].g = 0;
			} else {
				if(intersections.at(index_of_first_intersection) > accuracy ) { // jesli ta wartosc jest wieksza niz blad, to mozemy zalozyc ze idziemy po drugi obiekt

					vect& intersection_pos = cam_ray_origin.addVect(cam_ray_dir.multipVect(intersections.at(index_of_first_intersection)));
					vect& intersection_ray_direction = cam_ray_dir;

					Color& thisPixelColor = getColorAt(intersection_pos, intersection_ray_direction, scene_objects, index_of_first_intersection,scene_lights,accuracy,ambLight);

					pixel[arrayPoint].r = thisPixelColor.getR();
					pixel[arrayPoint].b = thisPixelColor.getB();
					pixel[arrayPoint].g = thisPixelColor.getG();

					glpixel[0][0][0] = thisPixelColor.getR() * 255;
					glpixel[0][0][1] = thisPixelColor.getG() * 255;
					glpixel[0][0][2] = thisPixelColor.getB() * 255;

					glRasterPos3f(i, j, 0);
					glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, glpixel);

				}
			}

		}
	}


	std::cout<<"nazewa bez bmp:\n";
	std::cin>> fileName;

	if( fileName.find(".") == std::string::npos ) {
		fileName = fileName + ".bmp";
	}

	saveBMP(fileName, width, hight, 72, pixel);

	system("pause");

	return 0;
}

