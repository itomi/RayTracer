#include "Command.h"

const char* Command::mapValToString[] = {"dimensions","background","global","sphere","source"};
Command::Command(void) { }
Command::Command( std::vector<std::string> command ) { 
	this->commandLine = command;
	std::string commandType = command.at(0);

	if( commandType == mapValToString[0]){
		cmdType = DIMENSION;
	} else if( commandType == mapValToString[1]) {
		cmdType = BACKGROUND;
	} else if( commandType == mapValToString[2]) {
		cmdType = GLOBAL;
	} else if( commandType == mapValToString[3]) {
		cmdType = SPHERE;
	} else if( commandType == mapValToString[4]) {
		cmdType = SOURCE;
	}

	handleValues();
}
Command::~Command(void) {}

void Command::handleValues() {
	switch(cmdType) {
	case BACKGROUND:
		for( int i = 0 ; i < 3 ; i++ )
			this->args.BackArgs.color[0] = std::stof(commandLine.at(i+1));
		break;
	case GLOBAL:
		for( int i = 0 ; i < 3 ; i++)
			this->args.GlobalLightArgs.color[i] = std::stof(commandLine.at(i+1));
		break;
	case DIMENSION:
			this->args.DimArgs.width = std::stoi(commandLine.at(1));
			this->args.DimArgs.hight = std::stoi(commandLine.at(2));
		break;
	case SOURCE:
			this->args.LightArgs.xpos = std::stof(commandLine.at(1));
			this->args.LightArgs.ypos = std::stof(commandLine.at(2));
			this->args.LightArgs.zpos = std::stof(commandLine.at(3));
			this->args.LightArgs.ambient[0] = std::stof(commandLine.at(4));
			this->args.LightArgs.ambient[1] = std::stof(commandLine.at(5));
			this->args.LightArgs.ambient[2] = std::stof(commandLine.at(6));
			this->args.LightArgs.diffuse[0] = std::stof(commandLine.at(7));
			this->args.LightArgs.diffuse[1] = std::stof(commandLine.at(8));
			this->args.LightArgs.diffuse[2] = std::stof(commandLine.at(9));
			this->args.LightArgs.specular[0] = std::stof(commandLine.at(10));
			this->args.LightArgs.specular[1] = std::stof(commandLine.at(11));
			this->args.LightArgs.specular[2] = std::stof(commandLine.at(12));

		break;
	case SPHERE:
		this->args.SphereArgs.radius = std::stof(commandLine.at(1));
		this->args.SphereArgs.xpos = std::stof(commandLine.at(2));
		this->args.SphereArgs.ypos = std::stof(commandLine.at(3));
		this->args.SphereArgs.zpos = std::stof(commandLine.at(4));
		this->args.SphereArgs.ambient[0] = std::stof(commandLine.at(5));
		this->args.SphereArgs.ambient[1] = std::stof(commandLine.at(6));
		this->args.SphereArgs.ambient[2] = std::stof(commandLine.at(7));
		this->args.SphereArgs.diffuse[0] = std::stof(commandLine.at(8));
		this->args.SphereArgs.diffuse[1] = std::stof(commandLine.at(9));
		this->args.SphereArgs.diffuse[2] = std::stof(commandLine.at(10));
		this->args.SphereArgs.specular[0] = std::stof(commandLine.at(11));
		this->args.SphereArgs.specular[1] = std::stof(commandLine.at(12));
		this->args.SphereArgs.specular[2] = std::stof(commandLine.at(13));
		this->args.SphereArgs.shinines = std::stoi(commandLine.at(14));
		break;
	default:
		throw new std::exception((std::string("Nieznany typ komendy: ") + commandLine.at(0)).c_str());
	}
}

Command::CommandType Command::getType() {
	return this->cmdType;
}
