#pragma once

#define SINGLETON_DYNAMIC(Type) \
private:\
	static inline Type* Instance;\
	using This = Type;\
public:\
	inline static bool IsExist() { return (bool)Instance;} \
	inline static Type* Get() noexcept\
	{\
		if(!Instance) \
		{\
			if(!Instance) Instance = new Type;\
		}\
		return Instance;\
	}\
	static void DestroyInstance()\
	{\
		SAFE_DELETE(Instance);\
	}\
private:\
	Type();\
	~Type();


#define SAFE_DELETE(x)			{ if(x) { delete x; x = nullptr; } }
#define _DEBUG_OUTPUT_LOG