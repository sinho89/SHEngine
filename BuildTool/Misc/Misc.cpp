#include "Misc.h"

void FSupportModules::UseModule(const std::string& NewModuleName)
{
	if (Modules.end() == Modules.find(NewModuleName))
	{
		std::cout << "[ERROR] Unsupported module: " << NewModuleName << std::endl;
		MessageBoxA(NULL, NewModuleName.c_str(), "[ixrBuildTool] Unsupported module", MB_OK);
		assert(false);
	}
	Modules[NewModuleName] = true;
}