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
	id = glGetUniformLocation (shader->program, name.c_str ());

	return id != -1;
}

std::vector<UniformCell> uniformCellStack;

std::vector<UniformCell> SwapUniformCellStack ()
{
	std::vector<UniformCell> oldStack = uniformCellStack;
	uniformCellStack.clear ();

	return oldStack;
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
		if (!uCell.Initialize (shader))
		{
			printf ("Unknown uniform named: \"%s\"!\n", uCell.name.c_str());
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
		XFN_UploadUniform fn = uCell.uploadFunctionPtr;
		(uCell.uniform->*fn)(uCell.id);
	}
}