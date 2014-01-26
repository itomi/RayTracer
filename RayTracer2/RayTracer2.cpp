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

static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}
void handleDimension(std::vector<std::string>& command) {
	imageSize = std::stoi(command.at(1));
}
void  handleBackgroud(std::vector<std::string>& command) {
	for( int i = 0 ; i < 3 ; i++)
		backColor[i] = std::stof(command.at(i+1));
}
void handleGlobalLight(std::vector<std::string>& command) {
	for( int i = 0 ; i < 3 ; i++)
		globalLight[i] = std::stof(command.at(i+1));
}
void handleSphere(std::vector<std::string>& command) {
	sphere_radius[spheresCounter] = std::stof(command.at(1));
	int i;
	for (i=0; i<3; i++)	
		sphere_position[spheresCounter][i] = std::stof(command.at(i+2));
	for (i=0; i<3; i++)
		sphere_specular[spheresCounter][i] = std::stof(command.at(1+5));
	for (i=0; i<3; i++)
		sphere_diffuse[spheresCounter][i] = std::stof(command.at(1+8));
	for (i=0; i<3; i++)	
		sphere_ambient[spheresCounter][i] = std::stof(command.at(1+11));

	sphere_specularhininess[spheresCounter] = std::stof(command.at(14));
	spheresCounter++;

}
void handleLight(std::vector<std::string>& command) {
	int i ;
	for (i=0; i<3; i++)	
		light_position[lightsCounter][i] = std::stof(command.at(i+1));
	for (i=0; i<3; i++)	
		light_specular[lightsCounter][i] = std::stof(command.at(i+4));
	for (i=0; i<3; i++)
		light_diffuse[lightsCounter][i] = std::stof(command.at(i+7));
	for (i=0; i<3; i++)
		light_ambient[lightsCounter][i] = std::stof(command.at(i+10));
	lightsCounter++;
}
void processCommand(std::vector<std::string>& command) {
	std::string& object = command.at(0);
	std::cout<<"Dlugosc komendy: "<<command.size()<<"\n";
	if( object == "dimensions" ) {
		handleDimension(command);
	} else if( object == "background") {
		handleBackgroud(command);
	} else if( object == "global") {
		handleGlobalLight(command);
	} else if( object == "sphere") {
		if(spheresCounter < MAX_SPHERES)
			handleSphere(command);
	} else if( object == "source") {
		if(lightsCounter < MAX_LIGHTS ) 
			handleLight(command);
	} else {
		std::cerr<<"nieznana komenda"<<command.at(0)<<"\n";
	}

}

void readCoommandsFromFile(std::string fileWithCommands) 
{
	std::fstream& dataFile = std::fstream(fileWithCommands, std::fstream::in);
	std::string lineBuffer = "";
	std::string temp = "";
	std::vector<std::string> temporaryCommand;

	if(dataFile.is_open()) {
		while(!dataFile.eof()) {
			std::getline(dataFile, lineBuffer);
			std::stringstream lineBuf(lineBuffer);
			int pos = 0;
			while (!lineBuf.eof()) {
				lineBuf >> temp;
				temporaryCommand.push_back(temp);
			}

			processCommand(temporaryCommand);
			temporaryCommand.clear();
		}
	} else {
		std::cout<<"Brak pliku "<<fileWithCommands<<"\n";
		system("pause");
		exit(0);
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

	bmpinfoheader[21] = (unsigned char) (s);
	bmpinfoheader[22] = (unsigned char) (s>>8);
	bmpinfoheader[23] = (unsigned char) (s>>16);
	bmpinfoheader[24] = (unsigned char) (s>>24);


	bmpinfoheader[25] = (unsigned char) (pixPerM);
	bmpinfoheader[26] = (unsigned char) (pixPerM>>8);
	bmpinfoheader[27] = (unsigned char) (pixPerM>>16);
	bmpinfoheader[28] = (unsigned char) (pixPerM>>24);


	bmpinfoheader[29] = (unsigned char) (pixPerM);
	bmpinfoheader[30] = (unsigned char) (pixPerM>>8);
	bmpinfoheader[31] = (unsigned char) (pixPerM>>16);
	bmpinfoheader[32] = (unsigned char) (pixPerM>>24);

	file.open(fileName, std::fstream::in | std::fstream::out | std::fstream::binary );

	file.write()

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

	vect& vec = vect(1.0,40.5,12.4);

	vect& newNormalized = vect::normalizeVect(vec);

	
	std::cout<<vec<<std::endl;
	std::cout<<newNormalized<<std::endl;
	std::cout<<vec<<std::endl;
	
	system("pause");

	return 0;
}

