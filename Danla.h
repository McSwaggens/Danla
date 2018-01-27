#pragma once


#include "Standard.h"
#include "SafeList.h"
#include "Entity.h"
#include "Actor.h"
#include "World.h"
#include "Math.h"
#include "Window.h"
#include "Time.h"
#include "Shapes.h"
#include "Material.h"

extern HWindow window;

extern HAttributeBuffer<Vector2> positionBuffer;
extern HWorld world;

MATERIAL(UnitMaterial)
	TEXTURE(u_Texture, 0);
END_MATERIAL;

extern HUnitMaterial unitMaterial;


void StartDanla ();
void ShutdownDanla ();
void PrintErrors ();

#ifdef HTEMPLATE
	#undef HTEMPLATE
#endif
