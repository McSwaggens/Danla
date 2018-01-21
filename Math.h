//
// Created by daniel on 1/14/2018.
//

#pragma once

#define PI 3.14159265358979323846
#define PIx2 (PI * 2)
#define PIx4 (PI * 4)

#include <cmath>

inline float Min (float f, float min)
{
	return f < min ? min : f;
}

inline float Max (float f, float max)
{
	return f > max ? max : f;
}

inline float Clamp (float f, float min, float max)
{
	return Min(Max(f, max), min);
}

inline Vector2 QuickCircle (float f)
{
	return Vector2(sin(f), cos(f));
}