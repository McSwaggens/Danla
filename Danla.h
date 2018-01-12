#pragma once


#include "Standard.h"
#include "Window.h"
#include "AttributeBuffer.h"
#include "Time.h"
#include "Shapes.h"

#define TEXUNIT0 0x84C0

extern HWindow window;

extern HAttributeBuffer<Vector2> positionBuffer;

void StartDanla ();
void ShutdownDanla ();
void PrintErrors ();

#ifdef HTEMPLATE
	#undef HTEMPLATE
#endif
