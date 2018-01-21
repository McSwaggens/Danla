//
// Created by daniel on 1/18/2018.
//

#pragma once

#include "Vector.h"

class IVector2 : public Vector
{
public:
	int x;
	int y;
	
	IVector2 ();
	IVector2 (int x);
	IVector2 (int x, int y);
	
	void UploadUniform (UniformID id);
};
