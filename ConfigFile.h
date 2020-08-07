#pragma once

#include "StringConvertor.h"

class ConfigFile
{
public:
	ConfigFile(std::string file);
	int ReadInterger(std::string section, std::string key);
	std::string ReadString(std::string section, std::string key);
	std::string GetFileName() const;
	bool IsValid() const;
	static void CreateConfigFile(std::string file);
private:
	std::string file_name = "";
	std::string file_path = "";
};