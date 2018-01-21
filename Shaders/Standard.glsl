/*
	Danla Standard Shader Library

		This file contains many helpfull functions that you can use in your glsl shaders.
		Feel free to add more usefull shader functions.
*/

vec4 GreyScale (in vec4 color)
{
	float avg = (color.r + color.g + color.b) / 3;
	return vec4(avg, avg, avg, color.a);
}

vec4 Tint (in vec4 color, in vec4 tint)
{
	vec4 grey = GreyScale(color);
	return grey * tint;
}