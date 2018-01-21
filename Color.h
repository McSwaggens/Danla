//
// Created by daniel on 1/14/2018.
//

#pragma once

#include "Standard.h"

class Color : Uniform
{
private:

public:
	
	float r;
	float g;
	float b;
	float a;
	
	Color ();
	Color (float r);
	Color (float r, float g, float b);
	Color (float r, float g, float b, float a);
	
	Color Clamped (float min = 0, float max = 1);
	Color ClampNoAlpha (float min = 0, float max = 1);

	void UploadUniform (UniformID id);
};

