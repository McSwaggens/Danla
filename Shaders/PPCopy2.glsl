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
uniform float time;

vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction)
{
	vec4 color = vec4(0.0);
	vec2 off1 = vec2(1.411764705882353) * direction;
	vec2 off2 = vec2(3.2941176470588234) * direction;
	vec2 off3 = vec2(5.176470588235294) * direction;
	color += texture2D(image, uv) * 0.1964825501511404;
	color += texture2D(image, uv + (off1 / resolution)) * 0.2969069646728344;
	color += texture2D(image, uv - (off1 / resolution)) * 0.2969069646728344;
	color += texture2D(image, uv + (off2 / resolution)) * 0.09447039785044732;
	color += texture2D(image, uv - (off2 / resolution)) * 0.09447039785044732;
	color += texture2D(image, uv + (off3 / resolution)) * 0.010381362401148057;
	color += texture2D(image, uv - (off3 / resolution)) * 0.010381362401148057;
	return color;
}

void main ()
{
	color = 1 - texture2D(u_InputTexture, uv);
}