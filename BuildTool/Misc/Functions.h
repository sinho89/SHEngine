#pragma once
#include "Misc.h"

inline static int MultiByteToWide(const char* src, wchar_t* dest)
{
	int len = ::MultiByteToWideChar(CP_ACP, 0, src, -1, dest, 0);
	return ::MultiByteToWideChar(CP_ACP, 0, src, -1, dest, len); //::mbstowcs(dest, src, len);        
}

inline static int AnsiToUtf8(const char* pszAnsi, char* pszUtf8)
{
	wchar_t wszTmp[1024];
	int len = MultiByteToWide(pszAnsi, wszTmp);
	len = ::WideCharToMultiByte(CP_UTF8, 0, wszTmp, -1, pszUtf8, 0, nullptr, nullptr);
	return ::WideCharToMultiByte(CP_UTF8, 0, wszTmp, -1, pszUtf8, len, nullptr, nullptr);
}

static void CopyTo(const std::string& Src, const std::string& Files, const std::string& Dst, const std::string& ExcludeFile = "", const std::string& Flags = "/S /Y /D /I")
{
	std::string CMD = "xcopy";
	std::string Exclude;
	if (ExcludeFile.size() > 0)
	{
		// " " ·Î °¨½Î´Â°Ô ¾ÈµÊ
		Exclude = "/exclude:" + ExcludeFile;
	}

	std::string FullCMD = CMD + " \"" + (Src + Files) + "\" \"" + Dst + "\" " + Flags + " " + Exclude;
	std::cout << "CMD: " << FullCMD << std::endl;
	system(FullCMD.c_str());
}