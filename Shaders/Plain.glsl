#version 440 core

#Vertex

layout (location = 0) in vec2 _vertexPosition;
layout (location = 1) in vec2 _uv;

// MVP Matrix?

out vec2 uv;
uniform float time;

void main ()
{
	gl_Position = vec4(_vertexPosition, 0, 1);
	uv = _uv;
}

#Fragment

out vec4 color;
in vec2 uv;

uniform float time;
uniform sampler2D u_InputTexture;
uniform sampler2D u_BloomTexture;

void main ()
{
	vec3 bloom = texture2D(u_BloomTexture, uv).rgb;
	vec3 col = texture2D(u_InputTexture, uv).rgb;

	//col += bloom;
	vec3 r = vec3(1.0) - exp(-col * 2.2);

	color = vec4(r, 1);
}