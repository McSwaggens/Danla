#version 440 core

#Vertex

layout (location = 0) in vec2 _vertexPosition;
layout (location = 1) in vec2 _uv;


uniform sampler2D u_InputTexture;

out vec2 uv;
out vec2 gaussianBlurTexCoords[11];

void main ()
{
	gl_Position = vec4(_vertexPosition, 0, 1);
	uv = _uv;

	const vec2 txSize = textureSize(u_InputTexture, 1);

	float pixelSize = 1 / txSize.x;

	for (int i = -5; i <= 5; i++)
	{
		gaussianBlurTexCoords[i + 5] = uv + vec2(pixelSize * i, 0.0);
	}

}

#Fragment

out vec4 color;
in vec2 uv;
in vec2 gaussianBlurTexCoords[11];

uniform sampler2D u_InputTexture;
uniform vec4 u_tint;
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
	vec4 sum = vec4(0);

	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[0]) * 0.090743;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[1]) * 0.090842;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[2]) * 0.09092;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[3]) * 0.090976;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[4]) * 0.091009;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[5]) * 0.09102;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[6]) * 0.091009;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[7]) * 0.090976;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[8]) * 0.09092;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[9]) * 0.090842;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[10]) * 0.090743;

	color = sum;

	//color = blur13(u_InputTexture, uv, textureSize(u_InputTexture, 1), vec2(1, 0));
}