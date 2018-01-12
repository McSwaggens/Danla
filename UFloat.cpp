//
// Created by daniel on 1/11/2018.
//

#include "UFloat.h"
#include "OpenGL.h"


UFloat::UFloat ()
{

}

UFloat::UFloat (float f)
{
	value = f;
}

void UFloat::UploadUniform (UniformID id)
{
	glUniform1f(id, value);
}
