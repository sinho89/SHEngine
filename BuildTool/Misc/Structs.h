#pragma once
#include "Misc.h"

struct FBuildPaths
{
	std::string SolutionPath;
	std::string BPSPath; // Build Property Sheet
	std::string DPSPath; // Directory Property Sheet
	std::string EPSPath; // Engine Configurations Property Sheet

	std::string ProjectPath;
	std::string EngineRootPath;
	std::string OutPath;

	std::string CorePath;	// g_BuildToolContext.EngineRootPath + "ixrEngine\\01.Core\\";
	std::string CoreAssetPath;	// CorePath + "Asset\\";
	std::string GraphicsPath;	// g_BuildToolContext.EngineRootPath + "ixrEngine\\03.Graphics\\";
	std::string GraphicsAssetPath;	// GraphicsPath + "Asset\\";
	std::string FrameworkPath;	// g_BuildToolContext.EngineRootPath + "ixrEngine\\04.Framework\\";
	std::string FrameworkAssetPath;	// FrameworkPath + "Asset\\";
	std::string FrameworkThirdPartyDllx86Path;	// FrameworkPath + "ThirdParty\\Dll\\x86\\";
	std::string FrameworkThirdPartyDllx64Path;	// FrameworkPath + "ThirdParty\\Dll\\x86\\";

	std::string ProjcetThirdPartyDllx86Path;	// ProjectDir + "ThirdParty\\Dll\\x86\\"; // 엔진 및 프로젝트에 있는 ThirdParty 하위 폴더의 x64\\Dll, x86\\Dll을 OutPath 복사하기 위함
	std::string ProjcetThirdPartyDllx64Path;	// ProjectDir + "ThirdParty\\Dll\\x64\\"; // 프로젝트에 있는 ThirdParty 하위 폴더의 x64\\Dll, x86\\Dll을 OutPath 복사하기 위함
	std::string ProjcetGraphicsAssetPath;	// ProjectDir + "Asset\\"; // 프로젝트에 있는 그래픽 리소스를 OutPath 복사하기 위함

};

struct FSupportModules
{
	FSupportModules()
	{
		//CoreMinimal
		Modules.insert(std::make_pair("USE_EASY_PROFILER_MODULE", false));

		//GraphicsMinimal
		Modules.insert(std::make_pair("USE_ENCODE_MODULE", false));
		Modules.insert(std::make_pair("USE_IMGUI_MODULE", false));
		Modules.insert(std::make_pair("NO_GRAPHICS_ASSET", false));
		Modules.insert(std::make_pair("NO_FBX_MODULE", false));

		//Framework
		Modules.insert(std::make_pair("USE_AWS_MODULE", false));
	}

	void UseModule(const std::string& ModuleName);

	std::unordered_map<std::string, bool> Modules;
};