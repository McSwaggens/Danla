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
	//printf ("Called on id %i\n", id);
	glDeleteTextures(1, &id);
	id = 0;
}

void Texture::UploadUniform (UniformID id)
{
	printf ("Texture UploadUniform called! This shouldn't happen!\n");
}

void Texture::Bind (TextureUnit textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit.unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::UploadUniformTexture (UniformID _id, TextureUnit textureUnit)
{
	Bind(textureUnit);
	glUniform1i(_id, textureUnit.unit);
}

void Texture::ClampMirror (bool x, bool y)
{
	if (x)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
	}
	
	if (y)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
	}
}

void Texture::EdgeClamp (bool x, bool y)
{
	if (x)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	}
	
	if (y)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
}

void Texture::Repeat (bool x, bool y)
{
	if (x)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	}
	
	if (y)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}

void Texture::MirroredRepeat (bool x, bool y)
{
	if (x)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	}
	
	if (y)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}
}

void Texture::SetInterpolationLinear ()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Texture::SetInterpolationNearest ()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


HTexture LoadTexture (String fileName)
{
	unsigned int textureID = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_AUTO, 0, SOIL_FLAG_INVERT_Y);
	
	if (!textureID)
	{
		printf ("Failed to load texture \"%s\".", fileName.c_str());
		return HTexture();
	}
	
	HTexture texture = new Texture (textureID);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	
	texture->MirroredRepeat(true, true);
	texture->SetInterpolationNearest();
	glGenerateMipmap(GL_TEXTURE_2D);
	
	
	return texture;
}