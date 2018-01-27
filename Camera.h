//
// Created by daniel on 1/22/2018.
//

#pragma once

#include "Handle.h"
_HCLASS(Camera);

#include "Standard.h"
#include "World.h"
#include "Math.h"

extern HCamera activeCamera;

HCLASS(Camera) : Object
{
private:
	
	const float aspectYScale = (9.0f/16.0f);
	Matrix4 pvMatrix;
	
public:
	
	Vector2 position;
	float zoom = 10.0f;
	
	Camera ();
	Camera (Vector3 position);
	
	void PreComputeMatrix ();
	void RenderWorld (HWorld world);
	
	inline float* GetMatrixPointer ()
	{
		return &pvMatrix.values[0];
	}
	
	inline Matrix4& GetMatrix ()
	{
		return pvMatrix;
	}
	
	inline bool IsCulled (Transform& target)
	{
		Vector2 relativePosition = Abs((target.position) - position);
		return relativePosition.x > (zoom+(target.scale.x*1.5f)) || relativePosition.y > ((zoom*aspectYScale)+(target.scale.y*1.5f));
	}
};



