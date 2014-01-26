#pragma once
#include <vector>
#include <string>

class Command
{
public:
	enum CommandType{
		DIMENSION,
		BACKGROUND,
		GLOBAL,
		SPHERE,
		SOURCE
	};

	union CommandArgs {
		struct SphereArg {
			float radius;
			float xpos,ypos,zpos;
			float specular[3];
			float diffuse[3];
			float ambient[3];
			int shinines;
		}SphereArgs;

		struct GlobalLightArg {
			float color [3]; // r,g,b
		}GlobalLightArgs;

		struct LightArg {
			float xpos,ypos,zpos;
			float specular[3];
			float diffuse[3];
			float ambient[3];
		}LightArgs;

		struct DimArg {
			int width,hight;
		}DimArgs;

		struct BackArg {
			float color[3];  // r,g,b
		}BackArgs;
	} args;
private:
	static const char* mapValToString[];
	CommandType cmdType;
	std::vector<std::string> commandLine;
public:
	Command(void);
	Command(std::vector<std::string> command);
	~Command(void);

	Command::CommandType getType();

	friend std::ostream& operator<<(std::ostream& os, const Command& command) {
		os<<"Command: [";
		for( std::string str : command.commandLine ) {
			os<<str<<" ";
		}
		os<<"]";
		return os;
	}
private:
	void handleValues();
};

