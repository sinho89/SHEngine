#include "DPSGenTask.h"

void FDPSGenTask::Task(const FBuildPaths& Paths)
{
	std::cout << "[ Generate DPS Starts ]\n";

	std::string Modules = "<Project>\n";

	Modules += "  <Import Project = " + DQM + Paths.EPSPath + DQM + " Condition=\"exists('" + Paths.EPSPath + "')\"/>\n";
	Modules += "  <Import Project = " + DQM + Paths.BPSPath + DQM + "/>\n";
	Modules += "</Project>\n";

	bool bSameFile = false;
	FILE* ImportModulesProp = nullptr;
	fopen_s(&ImportModulesProp, Paths.DPSPath.c_str(), "rb");
	if (ImportModulesProp)
	{
#ifdef _DEBUG_OUTPUT_LOG
		std::cout << "[ Already Props (ImportModulesProp != nullptr) ]\n";
#endif
		std::string OriginData;

		struct stat sb {};
		stat(Paths.DPSPath.c_str(), &sb);
		OriginData.resize(sb.st_size);
		fread(const_cast<char*>(OriginData.data()), sb.st_size, 1, ImportModulesProp);

		fclose(ImportModulesProp);

		if (OriginData == Modules)
		{
			bSameFile = true;
		}
	}

	if (!bSameFile)
	{
#ifdef _DEBUG_OUTPUT_LOG
		std::cout << "[ Different Props (bSameFile == false) ]\n";
#endif
		fopen_s(&ImportModulesProp, Paths.DPSPath.c_str(), "wb");
		if (ImportModulesProp)
		{
			fwrite(Modules.c_str(), Modules.size(), 1, ImportModulesProp);
			fclose(ImportModulesProp);
		}
	}

	std::cout << "[ Generate DPS Finish ]\n";
}