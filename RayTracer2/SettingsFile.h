#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "Command.h"

class SettingsFile {
	std::vector<Command > commands;

	SettingsFile(void);
	SettingsFile(std::string& fileName);
public:
	~SettingsFile(void);
	static SettingsFile& parseFile(std::string& fileName);



};

