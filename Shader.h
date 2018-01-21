#pragma once


#include "Standard.h"
#include "Handle.h"

extern String standardShaderLibraryString;

HCLASS(Shader) : public Object
{
public:
	int program = 0;
	
	Shader (int program);
	
	void Enable ();
	UniformID GetUniform (String name);
};

HShader CreateShader (String shaderName);