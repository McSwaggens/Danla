#version 440 core

#Vertex

layout (location = 0) in vec2 _vertexPosition;
layout (location = 1) in vec2 _uv;
layout (location = 2) in mat4 _matrix;

// MVP Matrix?

out vec2 uv;
uniform float time;
uniform mat4 pvMatrix;

void main ()
{
	gl_Position = pvMatrix * _matrix * vec4(_vertexPosition, 0.5, 1);
	uv = _uv;
}

#Fragment

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 hdr;
in vec2 uv;

uniform float time;

void main ()
{
	color = vec4(1, 0, 0, 1);
	hdr = vec4(5.0, 1, 13.0, 1);
}