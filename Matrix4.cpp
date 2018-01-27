//
// Created by daniel on 1/23/2018.
//


#include "Matrix4.h"

#include "OpenGL.h"


void Matrix4::UploadUniform (UniformID id)
{
	glUniformMatrix4fv(id, 1, false, &values[0]);
}
