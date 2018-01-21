//
// Created by daniel on 1/14/2018.
//

#pragma once

class TextureUnit
{
private:

public:
	unsigned int unit;
	
	TextureUnit ();
	TextureUnit (unsigned int textureUnit);
	
	unsigned int GetGLTextureUnit ();
	
	void Bind ();
};



