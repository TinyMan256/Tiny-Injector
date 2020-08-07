#pragma once

#include <Windows.h>
#include "StringConvertor.h"
#include "ConfigFile.h"

class Injector
{
public:
	bool Initialize(ConfigFile* const pConfigFile);
	void InjectDll();
private:
	void GetProcessId();

	std::string		process_name = "";
	std::wstring	process_name_wide = L"";
	std::string		TinyMan = "";
	std::wstring	TinyMan_wide = L"";
	std::string		dll_path = "";
	std::wstring	dll_path_wide = L"";
	ConfigFile*		pConfigFile = nullptr;
	DWORD			process_id = 0;
};