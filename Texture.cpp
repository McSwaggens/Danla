//
// Created by daniel on 1/8/2018.
//

#include "Texture.h"

#include "OpenGL.h"

Texture::Texture ()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture::Texture (Vector2 size) : Texture ()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)size.x, (int)size.y, 0, GL_RGB, GL_FLOAT, NULL);
}

Texture::Texture (unsigned int _id)
{
	id = _id;
}

Texture::~Texture ()
{
	Delete();
}

void Texture::Delete ()
{
	glDeleteTextures(1, &id);
	id = 0;
}

void Texture::UploadUniform (UniformID id)
{
	glUniform1i(id, this->id);
}

void Texture::Bind (int textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, id);
}
