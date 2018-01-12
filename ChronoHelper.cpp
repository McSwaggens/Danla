//
// Created by daniel on 1/7/2018.
//

#include "ChronoHelper.h"

#include <chrono>

TICKS GetSystemTime ()
{
	return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}
