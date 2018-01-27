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

out vec4 color;
in vec2 uv;

uniform float time;
uniform sampler2D u_Texture;

void main ()
{
	// 89 89 222
    // 140 184 255
	color = texture2D(u_Texture, uv);
	//color = vec4((uv.x + 0.5)* 0.5, 0, (uv.y + 0.7)* 0.5, 1);
}