//
// Created by daniel on 1/12/2018.
//

#pragma once

#include "AttributeBatch.h"

namespace Shapes
{
	extern HAttributeBatch quad;
	extern HAttributeBatch triangle;
	extern HAttributeBatch positionedTriangle;
	extern HAttributeBatch positionedQuad;
	extern HAttributeBatch matrixQuad;
	void Initialize ();
}

extern int drawCalls;

void DrawShape (HAttributeBatch shape);
