#pragma once
#ifndef NO_FBX_MODULE
#include <ixrEngine/03.Graphics/ThirdParty/FBXLoader/fbxsdk.h>
#ifdef _DEBUG

#ifndef _M_AMD64
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x86/debug/libfbxsdk-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/debug/libxml2-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/debug/zlib-md.lib")
#else
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/debug/libfbxsdk-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/debug/libxml2-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/debug/zlib-md.lib")
#endif

#else

#ifndef _M_AMD64
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x86/release/libfbxsdk-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x86/release/libxml2-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x86/release/zlib-md.lib")
#else
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/release/libfbxsdk-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/release/libxml2-md.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ThirdParty/FBXLoader/x64/release/zlib-md.lib")
#endif

#endif

#endif // NO_FBX_MODULE
