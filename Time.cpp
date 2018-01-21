//
// Created by daniel on 1/7/2018.
//


#include "Time.h"
#include "SystemTime.h"

// Private

TICKS ticks;
TICKS lastTicks;
TICKS startTicks = -1;
TICKS frequency;

float lastTime;

// Global

float time = 0.0f;
float delta = 0.0f;

#define WAIT_UNTIL_FRESH_TIME false

float TicksToSeconds (TICKS ticks)
{
	return (float)(ticks / (double)frequency);
}

void PollTimeFull ()
{
	if (startTicks == -1)
	{
		startTicks = GetSystemTime();
		
		frequency = GetSystemTimeFrequency();
	}

#if WAIT_UNTIL_FRESH_TIME
	do
	{
#endif
	
		ticks = GetSystemTime();
	
#if WAIT_UNTIL_FRESH_TIME
	} while (ticks == lastTicks);
#endif
	
	lastTime = time;
	
	time = TicksToSeconds(ticks - startTicks);
	
	delta = time - lastTime;
	
	lastTicks = ticks;
}


double GetTimeRaw ()
{
	return (GetSystemTime() / (double)frequency);
}

float GetTime ()
{
	return TicksToSeconds(GetSystemTime() - startTicks);
}
