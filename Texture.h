//
// Created by daniel on 1/8/2018.
//

#pragma once

#include "Danla.h"


HCLASS(Texture) : public Object, public Uniform
{
private:

public:
	
	unsigned int id = 0;
	
	Texture ();
	Texture (Vector2 size);
	Texture (unsigned int _id);
	
	~Texture ();
	
	void Delete();
	
	void UploadUniform (UniformID id);
	
	void Bind (int textureUnit = TEXUNIT0);
};



