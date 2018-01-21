#include "Material.h"
#include "OpenGL.h"
#include "UFloat.h"
#include <stdio.h>

UniformCell::UniformCell ()
{
}

UniformCell::UniformCell (Uniform* uniform, String name)
{
	this->uniform = uniform;
	this->name = name;
}

bool UniformCell::Initialize (HShader shader)
{
	id = glGetUniformLocation (static_cast<GLuint>(shader->program), name.c_str ());

	return id != -1;
}

void UniformCell::Upload ()
{
	XFN_UploadUniform fn = uploadFunctionPtr;
	(uniform->*fn)(id);
}

std::vector<UniformCell*> uniformCellStack;

std::vector<UniformCell*> SwapUniformCellStack ()
{
	std::vector<UniformCell*> oldStack = uniformCellStack;
	uniformCellStack.clear ();

	return oldStack;
}

HTexture CreateUniformTexture (String name, TextureUnit textureUnit)
{
	HTexture texture = new Texture ();
	
	UniformTextureCell* uCell = new UniformTextureCell(texture, name, textureUnit);
	
	uniformCellStack.push_back (uCell);
	
	return texture;
}

Material::Material ()
{
}

Material::Material (HShader shader)
{
	this->shader = shader;
}

void Material::Initialize (HShader shader)
{
	staticTime = shader->GetUniform("time");
	
	for (auto uCell : uniformCells)
	{
		if (!uCell->Initialize (shader))
		{
			printf ("Unknown uniform named: \"%s\"!\n", uCell->name.c_str());
		}
	}
}

void Material::Enable ()
{
	shader->Enable ();
	
	if (staticTime != -1)
	{
		glUniform1f(staticTime, time);
	}
	
	for (auto uCell : uniformCells)
	{
		uCell->Upload();
	}
}

Material::~Material ()
{
	uniformCells.clear(); // Make sure the pointers are cleared.
}

UniformTextureCell::UniformTextureCell (HTexture texture, String name, TextureUnit textureUnit)
{
	this->name = name;
	this->texture = texture;
	this->textureUnit = textureUnit;
}

void UniformTextureCell::Upload ()
{
	texture->UploadUniformTexture(id, textureUnit);
}
