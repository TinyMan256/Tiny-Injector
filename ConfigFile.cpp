#include "ConfigFile.h"
#include <Windows.h>
#include <fstream>

ConfigFile::ConfigFile(std::string file)
	: file_name(file)
{
	char* buffer = new char[MAX_PATH];
	GetFullPathNameA(file.c_str(), MAX_PATH, buffer, nullptr);
	this->file_path = std::string(buffer);
}

int ConfigFile::ReadInterger(std::string section, std::string key)
{
	return GetPrivateProfileIntA(section.c_str(), key.c_str(), 0, this->file_path.c_str());
}

std::string ConfigFile::ReadString(std::string section, std::string key)
{
	char* buffer = new char[255];
	GetPrivateProfileStringA(section.c_str(), key.c_str(), "INVALID", buffer, sizeof(buffer), this->file_path.c_str());
	std::string str(buffer);
	return str;
}

std::string ConfigFile::GetFileName() const
{
	return this->file_name;
}

bool ConfigFile::IsValid() const
{
	struct stat buffer;
	return (stat(this->file_name.c_str(), &buffer) == 0);
}

void ConfigFile::CreateConfigFile(std::string file)
{
	std::ofstream configFile(file);
	configFile << "[==================================|| Welcome to Tiny Injector ||==================================]\nTP=GTA5\nTD=Tiny\n";
	configFile.close();
}