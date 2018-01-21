//
// Created by daniel on 1/7/2018.
//


#include "SystemTime.h"

#if defined(__WIN32)
	#include <windows.h>
#else
	#include <chrono>
#endif

#if defined(__WIN32)
	LARGE_INTEGER ltime;
#endif

TICKS GetSystemTime ()
{
#ifdef _WIN32
	QueryPerformanceCounter(&ltime);
	return ltime.QuadPart;
#else
	return std::chrono::high_resolution_clock::now().time_since_epoch().count();
#endif
}

TICKS GetSystemTimeFrequency ()
{
#if defined(__WIN32)
	LARGE_INTEGER lfreq;
	QueryPerformanceFrequency(&lfreq);
	return lfreq.QuadPart;
#else
	return 1000000000;
#endif
}
