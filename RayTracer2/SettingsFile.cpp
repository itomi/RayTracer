#include "SettingsFile.h"


SettingsFile::SettingsFile(void) { }

SettingsFile::SettingsFile( std::string& fileName ) { }

SettingsFile::~SettingsFile(void) { }

SettingsFile& SettingsFile::parseFile( std::string& fileName ) {
	SettingsFile& file = *new SettingsFile(fileName);



}
