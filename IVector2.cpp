//
// Created by daniel on 1/18/2018.
//


#include "IVector2.h"
#include "OpenGL.h"

IVector2::IVector2 () : IVector2(0, 0)
{
}

IVector2::IVector2 (int x) : IVector2(x, x)
{
}

IVector2::IVector2 (int _x, int _y)
{
	x = _x;
	y = _y;
}

void IVector2::UploadUniform (UniformID id)
{
	glUniform2i(id, x, y);
}
