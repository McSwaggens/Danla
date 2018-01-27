//
// Created by daniel on 1/21/2018.
//


#include "Vector3.h"
#include "OpenGL.h"

Vector3::Vector3() : Vector3 (0, 0, 0)
{
}

Vector3::Vector3(float x) : Vector3 (x, x, x)
{
}

Vector3::Vector3(float x, float y) : Vector3 (x, y,  0)
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::Vector3 (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3::Vector3 (const Vector2& v, float _z)
{
	x = v.x;
	y = v.y;
	z = _z;
}

Vector3::Vector3 (const Vector2& v)
{
	x = v.x;
	y = v.y;
	z = 0;
}

void Vector3::UploadUniform (UniformID id)
{
	glUniform3f(id, x, y, z);
}
