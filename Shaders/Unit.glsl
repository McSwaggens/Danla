#version 440 core

#Vertex

layout (location = 0) in vec2 _vertexPosition;
layout (location = 1) in vec2 _uv;
layout (location = 2) in vec2 _position;
// MVP Matrix?

out vec2 uv;

void main ()
{
	gl_Position = vec4(((_vertexPosition / 2) + _position) * 0.5, 0, 1);
	uv = _uv;
}

#Fragment

out vec4 color;
in vec2 uv;

void main ()
{
	color = vec4((uv.x + 0.5)* 0.5, 0, (uv.y + 0.7)* 0.5, 1);
}