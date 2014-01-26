#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
class SettingsFile {
	std::vector<std::vector<std::string> > commands;

	SettingsFile(void);
	SettingsFile(std::string& fileName);
public:
	~SettingsFile(void);
	static SettingsFile& parseFile(std::string& fileName);
};

