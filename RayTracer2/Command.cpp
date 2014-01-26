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
		break;
	case SPHERE:
		break;
	default:
		throw new std::exception((std::string("Nieznany typ komendy: ") + commandLine.at(0)).c_str());
	}
}
