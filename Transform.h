//
// Created by daniel on 1/20/2018.
//

#pragma once

#include "Standard.h"



class Transform
{
private:
	friend class Camera;
	Matrix4 modelMatrix;
	
	Vector3 position;
	Vector2 scale;
	float rotation;
	
public:
	
	bool consistant = false;
	bool dirty = true;
	
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
	void Rotate (float f);
	
	Matrix4& GetMatrix ();
	
};
