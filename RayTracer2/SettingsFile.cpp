#include "SettingsFile.h"


SettingsFile::SettingsFile(void) { }

SettingsFile::SettingsFile( std::string& fileName ) { }

SettingsFile::~SettingsFile(void) { }

SettingsFile& SettingsFile::parseFile( std::string& fileName ) {
	SettingsFile& file = *new SettingsFile(fileName);

	std::fstream dataFile = std::fstream(fileName);
	std::string lineBuffer = "";
	std::string temp = "";
	std::vector<std::string> commandHolder;

	if(dataFile.is_open())
		while(!dataFile.eof()) {
			std::getline(dataFile, lineBuffer);
			std::stringstream lineBuf(lineBuffer);
				for( int i = 0 ; !lineBuf.eof() ; i++ ) {
					lineBuf >> temp;
					commandHolder.push_back(temp);
				}
				Command comm = Command(commandHolder);
				file.commands.push_back(comm);
			commandHolder.clear();
		}
	else
		throw new std::exception("Nie moge otworzyc pliku!");

	return file;
}
