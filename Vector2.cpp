#include "Vector2.h"
#include "OpenGL.h"


Vector2::Vector2() : Vector2 (0, 0)
{
}

Vector2::Vector2(float x) : Vector2 (x, x)
{
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Vector2::UploadUniform (UniformID id)
{
	glUniform2f(id, x, y);
}

Vector2::Vector2 (IVector2 iv2)
{
	x = iv2.x;
	y = iv2.y;
}
