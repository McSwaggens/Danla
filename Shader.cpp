#include "Shader.h"
#include "OpenGL.h"
#include "Standard.h"
#include "ShaderPreProcessor.h"

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <unistd.h>


Shader::Shader (int _program)
{
	program = _program;
}

void Shader::Enable ()
{
	glUseProgram (program);
}

UniformID Shader::GetUniform (String name)
{
	return glGetUniformLocation(program, name.c_str());
}

HShader CreateShader (String shaderName)
{
	printf ("Compiling shader \"%s\"\n", shaderName.c_str());
	
	int id = glCreateProgram ();
	
	HShader shader = new Shader (id);
	
	std::stringstream ss;

	char cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	
	ss << cwd << "/../Shaders/" << shaderName << ".glsl";
	std::ifstream fs (ss.str());
	String code ((std::istreambuf_iterator<char>(fs)), (std::istreambuf_iterator<char>()));
	std::vector<ShaderSource> sources = PreProcess (code);
	
	int logLength;
	for (int i = 0; i < sources.size(); i++)
	{
		ShaderSource source = sources[i];
		
		int shaderId = glCreateShader(source.type);
		
		const char* codeCStr = source.code.c_str();
		
		
		glShaderSource (shaderId, 1, &codeCStr, NULL);
		glCompileShader (shaderId);
		
		
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		
		if (logLength > 0)
		{
			std::vector<char> errorMessage (logLength + 1);
			glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
			
			printf ("SHADER COMPILE ERROR: %s\n", &errorMessage[0]);
			
			glDeleteProgram(shader->program);
			
			shader->program = 0;
			
			return shader;
		}
		
		glAttachShader (shader->program, shaderId);
	}
	
	glLinkProgram (shader->program);
	
	glGetProgramiv(shader->program, GL_INFO_LOG_LENGTH, &logLength);
	
	if (logLength > 0)
	{
		std::vector<char> errorMessage (logLength + 1);
		glGetProgramInfoLog(shader->program, logLength, NULL, &errorMessage[0]);
		
		printf ("PROGRAM LINK ERROR: %s\n", &errorMessage[0]);
		
		glDeleteProgram(shader->program);
		
		shader->program = 0;
		
		return shader;
	}
	
	return shader;
}