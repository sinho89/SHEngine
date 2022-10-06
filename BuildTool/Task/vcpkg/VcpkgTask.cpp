#include "VcpkgTask.h"

void FVcpkgTask::Task()
{
	system("..\\ThirdParty\\vcpkg\\bootstrap-vcpkg.bat");
	system("xcopy \"..\\ThirdParty\\triplets\" \"..\\ThirdParty\\vcpkg\\triplets\" /y /s");
	const std::string InstallCmd = "..\\ThirdParty\\vcpkg\\vcpkg.exe install ";
	const std::string Pkg = "DirectXTK DirectXTex magic-enum rapidjson ";
	const std::string Triplet_x64MD = " --triplet x64-windows --recurse";
	const std::string Triplet_x86MD = " --triplet x86-windows --recurse";
	const std::string Triplet_x64MT = " --triplet x64-windows-static --recurse";
	const std::string Triplet_x86MT = " --triplet x86-windows-static --recurse";

	// MD
	system((InstallCmd + Pkg + Triplet_x64MD).c_str());
	system((InstallCmd + Pkg + Triplet_x86MD).c_str());

	// MT
	system((InstallCmd + Pkg + Triplet_x64MT).c_str());
	system((InstallCmd + Pkg + Triplet_x86MT).c_str());

	system("..\\ThirdParty\\vcpkg\\vcpkg.exe integrate install");
}