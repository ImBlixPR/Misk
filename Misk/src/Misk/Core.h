#pragma once


#ifdef MK_PLATFORM_WINDOWS
	#ifdef MK_BUILD_DLL
		#define MISK_API __declspec(dllexport)
	#else
		#define MISK_API __declspec(dllimport)
	#endif // MK_BUILD_DLL
#else
	#error Misk only support Window!
#endif // MK_PLATFORM_WINDOW

#ifdef MK_ENABLE_ADDERTS
	#define MK_ASSERT(x, ...) { if(!(x)) {MK_ERROR("Assertion Failed here the problem: {0}", __VA_ARGS__); __debugbreak();}}
	#define MK_CORE_ASSERT(x, ...) { if(!(x)) {MK_CORE_ERROR("Assertion Failed here the problem: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define MK_ASSERT(x, ...)
	#define MK_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

