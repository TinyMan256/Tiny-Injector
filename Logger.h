#pragma once

#include "StringConvertor.h"

class Logger
{
public:
	static bool LogWarning(std::string message);
	static void LogError(std::string message);
	static void LogInfo(std::string message);
};