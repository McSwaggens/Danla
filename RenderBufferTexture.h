//
// Created by daniel on 1/8/2018.
//

#pragma once

#include "Danla.h"


HCLASS(RenderBufferTexture) : Object
{
private:

public:
	
	unsigned int id = 0;
	
	RenderBufferTexture ();
	RenderBufferTexture (unsigned int id);
	~RenderBufferTexture ();
	
	void Bind ();
};



