#pragma once

#ifdef BT_WINDOWS
	#ifdef BT_BUILD_DLL
		#define BOLT_API __declspec(dllexport)
	#else
		#define BOLT_API __declspec(dllimport)
	#endif
#else
	#error Supported only in windows
#endif
