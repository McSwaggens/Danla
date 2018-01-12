#pragma once

#include "Vector.h"

class Vector2 : public Vector
{
public:
	float x;
	float y;
	
	Vector2 ();
	Vector2 (float x);
	Vector2 (float x, float y);
	
	void UploadUniform (UniformID id);
};