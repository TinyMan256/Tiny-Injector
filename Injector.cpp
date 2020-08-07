#include "Injector.h"
#include "Logger.h"
#include <TlHelp32.h>

bool Injector::Initialize(ConfigFile* const pConfigFile)
{
	if (!pConfigFile->IsValid())
	{
		ConfigFile::CreateConfigFile(pConfigFile->GetFileName());
		Logger::LogInfo("Welcome to Tiny Injector");
		return false;
	}

	this->pConfigFile = pConfigFile;
	this->process_name = this->pConfigFile->ReadString("==================================|| Welcome to Tiny Injector ||==================================", "TP") + ".exe";
	this->process_name_wide = StringConvertor::StringToWide(this->process_name);
	this->TinyMan = this->pConfigFile->ReadString("==================================|| Welcome to Tiny Injector ||==================================", "TD") + ".dll";
	this->TinyMan_wide = StringConvertor::StringToWide(this->TinyMan);

	char* path_buffer = new char[MAX_PATH];
	GetFullPathNameA(this->TinyMan.c_str(), MAX_PATH, path_buffer, nullptr);
	this->dll_path = std::string(path_buffer);
	this->dll_path_wide = StringConvertor::StringToWide(this->dll_path);
	
	this->GetProcessId();

	struct stat file_buffer;
	if (stat(this->TinyMan.c_str(), &file_buffer) != 0)
	{
		Logger::LogError("Dll file not found or ini file changed");
		return false;
	}

	if (this->process_id == NULL)
	{
		Logger::LogError(" Run GTA5 First");
		return false;
	}

	return true;
}

void Injector::InjectDll()
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->process_id);
	if (hProc != INVALID_HANDLE_VALUE)
	{
		LPVOID alloc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		WriteProcessMemory(hProc, alloc, this->dll_path.c_str(), strlen(this->dll_path.c_str()) + 1, 0);
		HANDLE hThread = CreateRemoteThread(hProc, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, alloc, NULL, nullptr);
		if (hThread != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hThread);
		}
		else
		{
			Logger::LogError("Couldn't create remote thread");
		}

		CloseHandle(hProc);
	}
	else
	{
		Logger::LogError("Couldn't open PID: " + this->process_id);
	}
}

void Injector::GetProcessId()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, this->process_name_wide.c_str()))
				{
					this->process_id = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
}