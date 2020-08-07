#include "Logger.h"
#include <Windows.h>

bool Logger::LogWarning(std::string message)
{
	std::string warning_message = "Warning: " + message;
	int boxId = MessageBoxA(NULL, warning_message.c_str(), "Warning", MB_ICONWARNING | MB_OKCANCEL);

	switch (boxId)
	{
	case IDOK:
		return true;
	case IDCANCEL:
		return false;
	default:
		return false;
	}
}

void Logger::LogError(std::string message)
{
	std::string warning_message = "Error: " + message;
	MessageBoxA(NULL, warning_message.c_str(), "Error", MB_ICONERROR | MB_OK);
}

void Logger::LogInfo(std::string message)
{
	std::string warning_message = "Info: " + message;
	MessageBoxA(NULL, warning_message.c_str(), "Info", MB_ICONINFORMATION | MB_OK);
}