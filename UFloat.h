//
// Created by daniel on 1/11/2018.
//

#pragma once

#include "Standard.h"

class UFloat : public Uniform
{
private:

public:
	
	float value;
	
	UFloat ();
	UFloat (float f);
	
	void UploadUniform (UniformID id);
};



