//
// Created by daniel on 1/8/2018.
//

#pragma once

#include "Standard.h"
#include "TextureUnit.h"


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
	void UploadUniformTexture (UniformID id, TextureUnit textureUnit);
	void Bind (TextureUnit textureUnit);
	void ClampMirror (bool x = true, bool y = true);
	void MirroredRepeat (bool x = true, bool y = true);
	void Repeat (bool x = true, bool y = true);
	
	/**
	 * Pixelated then scaling.
	 */
	void SetInterpolationLinear();
	
	/**
	 * Blurred when scaling.
	 */
	void SetInterpolationNearest ();
};

typedef void (Texture::*XFN_UploadUniformTexture)(UniformID id, TextureUnit textureUnit);

HTexture LoadTexture (String fileName);
