//
// Created by daniel on 1/7/2018.
//


#include "Time.h"
#include "ChronoHelper.h"

// Private

TICKS ticks;
TICKS lastTicks;
TICKS startTicks = -1;

float lastTime;

// Global

float time = 0.0f;
float delta = 0.0f;

float TicksToSeconds (TICKS ticks)
{
	return (float)(ticks / 1000000000.0);
}

void PollTimeFull ()
{
	if (startTicks == -1)
	{
		startTicks = GetSystemTime();
	}
	
	do
	{
		ticks = GetSystemTime();
	} while (ticks == lastTicks);
	
	lastTime = time;
	
	time = TicksToSeconds(ticks - startTicks);
	
	delta = time - lastTime;
	
	lastTicks = ticks;
}


double GetTimeRaw ()
{
	return (GetSystemTime() / 1000000000.0);
}

float GetTime ()
{
	return TicksToSeconds(GetSystemTime() - startTicks);
}
