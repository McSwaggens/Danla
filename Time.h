//
// Created by daniel on 1/7/2018.
//

#pragma once


extern float time;
extern float frameDelta;
extern float logicDelta;
extern unsigned int tickRate;

/// @use Test!
float GetTime ();
double GetTimeRaw ();
void PollTimeFull ();
