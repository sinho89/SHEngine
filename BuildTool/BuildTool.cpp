#include "Misc/Misc.h"
#include "Task/vcpkg/VcpkgTask.h"

int main(int argc, char* argv[])
{
	std::cout << "[Build Tool Driving..]" << "\n";

	FBuildPaths BuildPaths;

#ifdef _DEBUG_OUTPUT_LOG
	for (int i = 0; i < argc; i++)
		std::cout << "argv[" << i << "] : " << argv[i] << "\n";

	std::cout << "argc : " << argc << "\n";
#endif
	
	if (argc >= (int)PathType::PT_SOLUTION)
	{
		std::string SolutionPath(argv[size_t(PathType::PT_SOLUTION)]);
		BuildPaths.SolutionPath = SolutionPath.substr(0, SolutionPath.rfind("\\..") + 1);
		FVcpkgTask VcpkgTask; VcpkgTask.Task();

#ifdef _DEBUG_OUTPUT_LOG
		std::cout << BuildPaths.SolutionPath << "\n";
#endif

	}

}