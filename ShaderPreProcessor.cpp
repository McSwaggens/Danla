#include "ShaderPreProcessor.h"
#include "OpenGL.h"

#include <map>

std::vector<String> Split (String code)
{
	std::vector<String> lines;
	String construct = "";
	
	for (int i = 0; i < code.size(); i++)
	{
		char c = code[i];
		
		if (c == '\n')
		{
			lines.push_back (construct);
			construct = "";
			continue;
		}
		
		construct += c;
	}
	lines.push_back (construct);
	
	return lines;
}

const std::map<String, int> flags { { "#Fragment", GL_FRAGMENT_SHADER }, { "#Vertex", GL_VERTEX_SHADER }, { "#Geometry", GL_GEOMETRY_SHADER } };

std::vector<ShaderSource> PreProcess (String code)
{
	int currentShader = 0;
	String header = "";
	String current = "";
	
	std::vector<ShaderSource> sources;
	
	std::vector<String> lines = Split (code);
	
	
	
	for (int i = 0; i < lines.size(); i++)
	{
		String line = lines[i];
		
		if (line.size() > 0)
		{
			if (line[0] == '#')
			{
				std::map<String, int>::const_iterator it = flags.find(line);
				
				if (it != flags.end())
				{
					if (currentShader == 0)
					{
						header = current;
						
						// printf ("Header: %s\n", header.c_str());
					}
					else
					{
						// printf ("Finished region: %s\n", current.c_str());
						
						ShaderSource shaderSource;
						shaderSource.code = current;
						shaderSource.type = currentShader;
						
						sources.push_back (shaderSource);
					}
					
					current = header;
					
					currentShader = it->second;
					
					continue;
				}
			}
			
			current.append(line + "\n");
			
		}
	}
	
	// printf ("Finished region: %s\n", current.c_str());
						
	ShaderSource shaderSource;
	shaderSource.code = current;
	shaderSource.type = currentShader;
	
	sources.push_back (shaderSource);
	
	return sources;
}