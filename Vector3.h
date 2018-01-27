//
// Created by daniel on 1/21/2018.
//

class Vector3;

#pragma once

#include "Vector2.h"
#include "Uniform.h"

class Vector3 : public Uniform
{
public:
	float x;
	float y;
	float z;
	
	Vector3 ();
	Vector3 (float x);
	Vector3 (float x, float y);
	Vector3 (float x, float y, float z);
	Vector3 (const Vector3& v);
	Vector3 (const Vector2& v, float z);
	Vector3 (const Vector2& v);
	
	inline operator Vector2()
	{
		return Vector2(x, y);
	}
	
	void UploadUniform (UniformID id);
	
	// Overloads
	
	//region Vector2 comparison
	
	inline bool operator == (const Vector2& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	
	inline bool operator != (const Vector2& rhs)
	{
		return x != rhs.x || y != rhs.y;
	}
	
	inline bool operator < (const Vector2& rhs)
	{
		return x < rhs.x && y < rhs.y;
	}
	
	inline bool operator > (const Vector2& rhs)
	{
		return x > rhs.x && y > rhs.y;
	}
	
	inline bool operator <= (const Vector2& rhs)
	{
		return x <= rhs.x && y <= rhs.y;
	}
	
	inline bool operator >= (const Vector2& rhs)
	{
		return x >= rhs.x && y >= rhs.y;
	}
	
	//endregion
	
	//region Vector3 comparison
	
	inline bool operator == (const Vector3& rhs)
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}
	
	inline bool operator != (const Vector3& rhs)
	{
		return x != rhs.x && y != rhs.y && z != rhs.z;
	}
	
	inline bool operator < (const Vector3& rhs)
	{
		return x < rhs.x && y < rhs.y && z < rhs.z;
	}
	
	inline bool operator > (const Vector3& rhs)
	{
		return x > rhs.x && y > rhs.y && z > rhs.z;
	}
	
	inline bool operator <= (const Vector3& rhs)
	{
		return x <= rhs.x && y <= rhs.y && z <= rhs.z;
	}
	
	inline bool operator >= (const Vector3& rhs)
	{
		return x >= rhs.x && y >= rhs.y && z >= rhs.z;
	}
	
	//endregion
	
	//region Float comparison
	
	inline bool operator == (const float& rhs)
	{
		return x == rhs && y == rhs && z == rhs;
	}
	
	inline bool operator != (const float& rhs)
	{
		return x != rhs && y != rhs && z != rhs;
	}
	
	inline bool operator < (const float& rhs)
	{
		return x < rhs && y < rhs && z < rhs;
	}
	
	inline bool operator > (const float& rhs)
	{
		return x > rhs && y > rhs && z > rhs;
	}
	
	inline bool operator <= (const float& rhs)
	{
		return x <= rhs && y <= rhs && z <= rhs;
	}
	
	inline bool operator >= (const float& rhs)
	{
		return x >= rhs && y >= rhs && z >= rhs;
	}
	
	//endregion
	
	//region Arithmetic assignment operators
	
	//region Vector2
	
	inline Vector3& operator += (const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	
	inline Vector3& operator -= (const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	
	inline Vector3& operator *= (const Vector2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	
	inline Vector3& operator /= (const Vector2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}
	
	//endregion
	
	//region Vector3
	
	inline Vector3& operator += (const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	
	inline Vector3& operator -= (const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	
	inline Vector3& operator *= (const Vector3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}
	
	inline Vector3& operator /= (const Vector3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}
	
	//endregion
	
	//region float
	
	inline Vector3& operator += (const float& rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}
	
	inline Vector3& operator -= (const float& rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}
	
	inline Vector3& operator *= (const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	
	inline Vector3& operator /= (const float& rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}
	//endregion

	//endregion
	
	//region Vector3 with Vector2 math operators
	
	inline Vector3 operator + (const Vector2& rhs)
	{
		return Vector3(x + rhs.x, y + rhs.y, z);
	}
	
	inline Vector3 operator - (const Vector2& rhs)
	{
		return Vector3(x - rhs.x, y - rhs.y, z);
	}
	
	inline Vector3 operator * (const Vector2& rhs)
	{
		return Vector3(x * rhs.x, y * rhs.y, z);
	}
	
	inline Vector3 operator / (const Vector2& rhs)
	{
		return Vector3(x / rhs.x, y / rhs.y, z);
	}

	//endregion
	
	//region Vector3 with Vector3 math operators
	
	inline Vector3 operator + (const Vector3& rhs)
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	
	inline Vector3 operator - (const Vector3& rhs)
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	
	inline Vector3 operator * (const Vector3& rhs)
	{
		return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
	}
	
	inline Vector3 operator / (const Vector3& rhs)
	{
		return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
	}
	
	//endregion
};