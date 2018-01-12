#include "Object.h"
#include <stdio.h>

#include "Handle.h"

Object::Object ()
{
	link = new HandleLink(this);
}

Object::~Object ()
{
	link->SoftUnlink ();
}