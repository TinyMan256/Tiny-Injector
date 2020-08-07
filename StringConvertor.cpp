#include "StringConvertor.h"

std::wstring StringConvertor::StringToWide(std::string str)
{
	std::wstring wstr(str.begin(), str.end());
	return wstr;
}