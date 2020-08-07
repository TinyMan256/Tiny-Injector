#include "Injector.h"
#include "Logger.h"

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	ConfigFile configFile("Tiny Injector.ini");
	Injector injector;

	if (injector.Initialize(&configFile))
	{
		
			injector.InjectDll();
		
	}

	return 0;
}