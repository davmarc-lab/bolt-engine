#pragma once

#ifdef BT_WINDOWS
	#if defined BT_BUILD_DLL || defined __CYGWIN__
		#define BOLT_API __declspec(dllexport)
	#else
		#define BOLT_API __declspec(dllimport)
	#endif
#else
    #if defined  __GNUC__
        #define BOLT_API __attribute__ ((visibility ("default")))
    #else
        #error Platform not supported.
    #endif
#endif

// asserts
/*
* Basic runtime assert.
*/
#define BT_ASSERT(exp) assert(exp)

