#version 440 core

#Vertex

layout (location = 0) in vec2 _vertexPosition;
layout (location = 1) in vec2 _uv;

out vec2 uv;

void main ()
{
	gl_Position = vec4(_vertexPosition, 0, 1);
	uv = _uv;
}

#Fragment

out vec4 color;
in vec2 uv;

uniform sampler2D u_InputTexture;
uniform sampler2D u_DepthTexture;

void main ()
{
	vec4 inputColor = texture2D(u_InputTexture, uv);
	float depth = texture2D(u_DepthTexture, uv).r;

	float flooredDepth = floor(depth);
	color = vec4(flooredDepth, flooredDepth, flooredDepth, 1);
}