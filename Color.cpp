//
// Created by daniel on 1/14/2018.
//

#include "Color.h"
#include "Math.h"
#include "OpenGL.h"

Color::Color () : Color (0, 0, 0, 1)
{
}

Color::Color (float r) : Color (r, r, r, 1)
{
}

Color::Color (float r, float g, float b) : Color (r, g, b, 1)
{
}

Color::Color (float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

Color Color::Clamped (float min, float max)
{
	return Color(Clamp(r, min, max), Clamp(g, min, max), Clamp(b, min, max), Clamp(a, min, max));
}

Color Color::ClampNoAlpha (float min, float max)
{
	return Color(Clamp(r, min, max), Clamp(g, min, max), Clamp(b, min, max), a);
}

void Color::UploadUniform (UniformID id)
{
	glUniform4f(id, r, g, b, a);
}
