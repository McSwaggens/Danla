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

inline float Reverse (float f)
{
	return (f * 1.0f) * -1.0f;
}

inline Vector2 Reverse (Vector2& v)
{
	return Vector2(Reverse(v.x), Reverse(v.y));
}

inline Vector3 Reverse (Vector3& v)
{
	return Vector3(Reverse(v.x), Reverse(v.y), Reverse(v.z));
}

inline Vector2 QuickCircle (float f)
{
	return Vector2(sin(f), cos(f));
}

inline float Mix (float x, float y, float a)
{
	return x * (1 - a) + y * a;
}

inline Vector2 Mix (Vector2 x, Vector2 y, float a)
{
	return x * (1.0f - a) + y * a;
}

inline Vector2 Abs (Vector2 v)
{
	return Vector2(fabsf(v.x), fabsf(v.y));
}