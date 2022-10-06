#include "Misc/Misc.h"
#include "Task/Vcpkg/VcpkgTask.h"
#include "Task/GenProps/DPSGenTask.h"
#include "Task/GenProps/EPSGenTask.h"

// Property Sheet를 활용하여 빌드에 필요한 환경 설정하는 도구

int main(int argc, char* argv[])
{
	std::cout << "[Build Tool Start]" << "\n";

	FBuildPaths BuildPaths = {};
	FSupportModules SupportModules = {};

	std::vector<std::string> vecArgs;

	{
		std::cout << "Token PushBack (vecArgs)" << "\n";
		char* token = nullptr;
		for (int i = 0; i <= argc; ++i)
		{
			token = argv[i];
			if (token == nullptr)
				break;

			vecArgs.push_back(token);
		}
	}

	const size_t ArgSize = vecArgs.size();
	
	
	std::string SolutionPath(vecArgs[size_t(PathType::PT_SOLUTION)]);
	BuildPaths.SolutionPath = SolutionPath.substr(0, SolutionPath.rfind("\\..") + 1);
	BuildPaths.BPSPath = BuildPaths.SolutionPath + "BuildTool\\ToolBuildSetting.props";
	BuildPaths.DPSPath = BuildPaths.SolutionPath + "DirectoryBuildSetting.props";
	BuildPaths.EPSPath = BuildPaths.SolutionPath + "Engine\\EngineBuildSetting.props";

	if (ArgSize == (int)PathType::PT_PROJECT)
	{
		FVcpkgTask	VcpkgTask;	VcpkgTask.Task();
		FDPSGenTask DPSTask;	DPSTask.Task(BuildPaths);
		return 0;
	}

	std::string ProjectPath(vecArgs[size_t(PathType::PT_PROJECT)]);
	BuildPaths.ProjectPath = ProjectPath.substr(0, ProjectPath.rfind("\\..") + 1);
	std::string EngineRootPath(vecArgs[size_t(PathType::PT_ENGINEROOT)]);
	BuildPaths.EngineRootPath = EngineRootPath + "\\";
	std::string OutPath(vecArgs[size_t(PathType::PT_OUTPUT)]);
	BuildPaths.OutPath = OutPath + "\\";

	BuildPaths.CorePath = BuildPaths.EngineRootPath + "Core\\";
	BuildPaths.CoreAssetPath = BuildPaths.CorePath + "Asset\\Asset\\";
	BuildPaths.GraphicsPath = BuildPaths.EngineRootPath + "Graphics\\";
	BuildPaths.GraphicsAssetPath = BuildPaths.GraphicsPath + "Asset\\";
	BuildPaths.FrameworkPath = BuildPaths.EngineRootPath + "Framework\\";
	BuildPaths.FrameworkAssetPath = BuildPaths.FrameworkPath + "Asset\\";

	BuildPaths.FrameworkThirdPartyDllx86Path = BuildPaths.FrameworkPath + "ThirdParty\\Dll\\x86\\";
	BuildPaths.FrameworkThirdPartyDllx64Path = BuildPaths.FrameworkPath + "ThirdParty\\Dll\\x64\\";
	BuildPaths.ProjcetThirdPartyDllx86Path = BuildPaths.ProjectPath + "ThirdParty\\Dll\\x86\\";
	BuildPaths.ProjcetThirdPartyDllx64Path = BuildPaths.ProjectPath + "ThirdParty\\Dll\\x64\\";
	BuildPaths.ProjcetGraphicsAssetPath = BuildPaths.ProjectPath + "Asset\\";
		
	const int ModuleStartIndex = 5;
	const int ModuleEnd = argc;

	for (int i = ModuleStartIndex; i < ModuleEnd; ++i)
	{
		SupportModules.UseModule(vecArgs[i]);
	}
	
	FEPSGenTask EPSGenTask;		EPSGenTask.Task(BuildPaths, SupportModules);

	std::cout << BuildPaths.SolutionPath << "\n";
	std::cout << BuildPaths.ProjectPath << "\n";
	std::cout << BuildPaths.EngineRootPath << "\n";
	std::cout << BuildPaths.OutPath << "\n";
	std::cout << BuildPaths.BPSPath << "\n";
	std::cout << BuildPaths.DPSPath << "\n";
	std::cout << BuildPaths.EPSPath << "\n";
	std::cout << "argc : " << argc << "\n";

	std::cout << "[Build Tool Done]" << "\n";
}