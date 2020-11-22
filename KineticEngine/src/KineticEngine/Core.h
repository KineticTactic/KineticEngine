#pragma once

#ifdef KE_PLATFORM_WINDOWS
#ifdef KE_BUILD_DLL
#define KE_API __declspec(dllexport)
#else 
#define KE_API __declspec(dllimport)
#endif
#else
#error Kinetic Engine only supports Windows!
#endif

