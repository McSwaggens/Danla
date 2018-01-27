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

void main ()
{
	vec4 sum = vec4(0);

	sum += texture(u_InputTexture, gaussianBlurTexCoords[0]) * 0.090743;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[1]) * 0.090842;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[2]) * 0.09092;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[3]) * 0.090976;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[4]) * 0.091009;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[5]) * 0.09102;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[6]) * 0.091009;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[7]) * 0.090976;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[8]) * 0.09092;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[9]) * 0.090842;
	sum += texture(u_InputTexture, gaussianBlurTexCoords[10]) * 0.090743;

	color = sum;
}