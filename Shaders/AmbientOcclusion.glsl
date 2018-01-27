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
uniform sampler2D u_BlurredDepth;
uniform sampler2D u_DepthTexture;

void main ()
{
	vec4 blurredDepth = texture2D(u_BlurredDepth, uv);
	vec4 screenColor = texture2D(u_InputTexture, uv);
	vec4 depthBuffer = texture2D(u_DepthTexture, uv);

	vec4 ao = ceil(1-((depthBuffer))) + blurredDepth;
	color = vec4(mix(screenColor.rgb, vec3(0, 0, 0), (1-ao.r) * floor(depthBuffer.r)), 1);
//	color = ao;
}