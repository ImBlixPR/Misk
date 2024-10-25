#pragma once


#ifdef MK_PLATFORM_WINDOW
	#ifdef MK_BUILD_DLL
		#define MISK_API __declspec(dllexport)
	#else
		#define MISK_API __declspec(dllimport)
	#endif // MK_BUILD_DLL
#else
	#error Misk only support Window!
#endif // MK_PLATFORM_WINDOW




#define BIT(x) (1 << x)

