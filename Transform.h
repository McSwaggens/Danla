//
// Created by daniel on 1/20/2018.
//

#pragma once

#include "Standard.h"



class Transform
{
	Matrix4 modelMatrix;
	
public:
	Vector3 position;
	Vector2 scale;
	float rotation;
	
	bool consistant = false;
	
	Transform ();
	Transform (const Vector3& position, const Vector2& scale, float rotation);
	
	inline Vector3 GetPosition () const
	{
		return position;
	}
	
	inline Vector2 GetScale () const
	{
		return scale;
	}
	
	inline float GetRotation () const
	{
		return rotation;
	}
	
	void SetPosition (Vector2 v);
	void Move (Vector2 v);
	void SetScale (Vector2 v);
	void SetRotation (float f);
	
	Matrix4& GetMatrix ();
	
};
