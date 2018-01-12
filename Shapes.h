//
// Created by daniel on 1/12/2018.
//

#pragma once

#include "Danla.h"
#include "AttributeBatch.h"

namespace Shapes
{
	extern HAttributeBatch quad;
	extern HAttributeBatch triangle;
	extern HAttributeBatch positionedTriangle;
	extern HAttributeBatch positionedQuad;
	void Initialize ();
}

void DrawShape (HAttributeBatch shape);
