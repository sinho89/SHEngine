#include "EPSGenTask.h"

void FEPSGenTask::Task(const FBuildPaths& Paths, FSupportModules& SupportModules)
{
	std::cout << "\n[Generate EPS Start]\n";

	std::string Modules = "<Project>\n";
	/*Modules += "  <ImportGroup Label=\"PropertySheets\" />\n";
	Modules += "  <PropertyGroup Label=\"UserMacros\" />\n";
	Modules += "  <PropertyGroup />\n";*/
	Modules += "  <ItemDefinitionGroup>\n";
	Modules += "    <ClCompile>\n";
	Modules += "      <PreprocessorDefinitions>";

	for (auto& iter : SupportModules.Modules)
	{
		if (iter.second == true)
		{
			const std::string Messsage = "Request Module: " + iter.first + "\n";
			std::cout << (Messsage.c_str());

			Modules += iter.first;
			Modules += ";";
		}
	}

	Modules += "%(PreprocessorDefinitions)</PreprocessorDefinitions>\n";
	// 추가 포함 디렉터리
	{
		Modules += "      <AdditionalIncludeDirectories>";

		Modules += DQM + Paths.EngineRootPath + DQM + Semicolon;
		//Modules += DQM + g_BuildToolContext.EngineRootPath + "ixrEngine" + DQM + Semicolon;

		// Graphics
		Modules += DQM + Paths.GraphicsPath + "ThirdParty\\imgui" + DQM + Semicolon;
		Modules += DQM + Paths.GraphicsPath + "ThirdParty\\FBXLoader" + DQM + Semicolon;
		Modules += DQM + Paths.GraphicsPath + "Encode\\ThirdParty\\ffmpeg\\include" + DQM + Semicolon;

		// Framework
		// AWS
		Modules += DQM + Paths.FrameworkPath + "ThirdParty\\AWS\\include" + DQM + Semicolon;

		//Modules += DQM + ProjectDir + DQM + Semicolon;

		Modules += "%(AdditionalIncludeDirectories)";

		Modules += "</AdditionalIncludeDirectories>\n";
	}
	Modules += "    </ClCompile>\n";

	// Link
	{
		Modules += "    <Link>\n";

		// 지연 DLL
		{
			Modules += "      <DelayLoadDLLs>";
			if (SupportModules.Modules["USE_ENCODE_MODULE"] == true)
			{
				Modules += "nvcuda.dll;";
			}
			Modules += "</DelayLoadDLLs>\n";
		}

		// 추가 라이브러리 디렉터리
		{
			Modules += "      <AdditionalLibraryDirectories>";

			Modules += DQM + Paths.EngineRootPath + DQM + Semicolon;

			// Framework
			Modules += DQM + Paths.FrameworkPath + "ThirdParty\\AWS\\lib" + DQM + Semicolon;

			Modules += "%(AdditionalLibraryDirectories)";

			Modules += "</AdditionalLibraryDirectories>\n";
		}

		Modules += "    </Link>\n";
	}

	Modules += "  </ItemDefinitionGroup>\n";
	//Modules += "  <ItemGroup />\n";
	Modules += "</Project>";

	bool bSameFile = false;
	FILE* ImportModulesProp = nullptr;
	fopen_s(&ImportModulesProp, Paths.EPSPath.c_str(), "rb");
	if (ImportModulesProp)
	{
		std::string OriginData;

		struct stat sb {};
		stat(Paths.EPSPath.c_str(), &sb);
		OriginData.resize(sb.st_size);
		fread(const_cast<char*>(OriginData.data()), sb.st_size, 1, ImportModulesProp);

		fclose(ImportModulesProp);

		//std::cout << OriginData << std::endl;
		//std::cout << Modules;

		if (OriginData == Modules)
		{
			std::cout << "[Skip]\n";
			bSameFile = true;
		}
		else
		{
			std::cout << "[Success]\n";
		}
	}

	{
		if (SupportModules.Modules["USE_ENCODE_MODULE"] == true)
		{
			CopyTo(Paths.GraphicsPath + "Encode\\ThirdParty\\ffmpeg\\bin\\", "*.dll", Paths.OutPath);
		}
		else if (SupportModules.Modules["USE_EASY_PROFILER_MODULE"] == true)
		{
			CopyTo(Paths.EngineRootPath + "ThirdParty\\easy_profiler-v2.1.0\\bin\\", "*.dll", Paths.OutPath);
		}
	}

	if (!bSameFile)
	{
		fopen_s(&ImportModulesProp, Paths.EPSPath.c_str(), "wb");
		if (ImportModulesProp)
		{
			fwrite(Modules.c_str(), Modules.size(), 1, ImportModulesProp);
			fclose(ImportModulesProp);
		}
	}
}