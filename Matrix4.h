//
// Created by daniel on 1/23/2018.
//

#pragma once

#include "Uniform.h"

class Matrix4 : Uniform
{
public:
	float values[16];
	
	void UploadUniform (UniformID id);
};