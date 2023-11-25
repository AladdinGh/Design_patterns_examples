
//#pragma once
#include <stdbool.h>
//# ifndef __FIBLIBRARY_H__
//#define __FIBLIBRARY_H__

// declspec is a windows specific feature and not available in linux, we need to add this 
// in the header file or in every file that contains the declspec(dllimport) or declspec(dllexport)
// command, this will basically ignore any __declspec() call on the processor level
#ifdef __linux__
#define __declspec(v)
#endif

// define API as an import public symbols defined by a DLL
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

//C++ functions are subject to name mangling. This makes them impossible to call directly from C 
//code unless extern "C" is used.


//ifdef __cplusplus
//extern "C"
//{
//#endif

	MATHLIBRARY_API void fibonacci_init(const unsigned long long a,const unsigned long long b); 
	MATHLIBRARY_API bool fibonacci_next();
	MATHLIBRARY_API long long fibonacci_current();	
	MATHLIBRARY_API unsigned fibonacci_index(); 


//#ifdef __cplusplus
//}
//#endif

