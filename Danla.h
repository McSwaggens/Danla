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

class UnitMaterial;using HUnitMaterial=Handle<UnitMaterial>;;class UnitMaterial:public Material{public:inline UnitMaterial(HShader shader):Material(shader){this->uniformCells=SwapUniformCellStack();Initialize(shader);}};

extern HUnitMaterial unitMaterial;


void StartDanla ();
void ShutdownDanla ();
void PrintErrors ();

#ifdef HTEMPLATE
	#undef HTEMPLATE
#endif
