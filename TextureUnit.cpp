//
// Created by daniel on 1/14/2018.
//

#include "TextureUnit.h"
#include "OpenGL.h"

TextureUnit::TextureUnit ()
{
	this->unit = 0;
}

TextureUnit::TextureUnit (unsigned int textureUnit)
{
	this->unit = textureUnit;
}

void TextureUnit::Bind ()
{
	glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + unit));
}

unsigned int TextureUnit::GetGLTextureUnit ()
{
	return GL_TEXTURE0 + unit;
}
