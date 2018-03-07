#version 440 core

#Vertex

layout (location = 0) in vec2 _vertexPosition;
layout (location = 1) in vec2 _uv;


uniform sampler2D u_InputTexture;
uniform float u_Split;

out vec2 uv;
out vec2 gaussianBlurTexCoords[5];

void main ()
{
	gl_Position = vec4(_vertexPosition, 0, 1);
	uv = _uv;

	const vec2 txSize = textureSize(u_InputTexture, 1);

	float pixelSize = 1 / txSize.x;

	for (int i = -2; i <= 2; i++)
	{
		gaussianBlurTexCoords[i + 2] = uv + vec2((pixelSize * u_Split) * i, 0.0);
	}

}

#Fragment

out vec4 color;
in vec2 uv;
in vec2 gaussianBlurTexCoords[5];

uniform sampler2D u_InputTexture;
uniform float time;

void main ()
{
	vec4 sum = vec4(0);

	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[0]) * 0.153388;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[1]) * 0.221461;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[2]) * 0.749698;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[3]) * 0.221461;
	sum += texture2D(u_InputTexture, gaussianBlurTexCoords[4]) * 0.153388;

	color = sum;

	//color = blur13(u_InputTexture, uv, textureSize(u_InputTexture, 1), vec2(1, 0));
}