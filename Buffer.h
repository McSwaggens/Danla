#pragma once

#include "Object.h"

HCLASS(Buffer) : Object
{
public:
	unsigned int buffer;
	
	Buffer ();
	Buffer (unsigned int _buffer);
	void Bind ();
	void Bind (int target);
};
