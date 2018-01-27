#pragma once

#include "Uniform.h"
#include "IVector2.h"

class Vector2 : public Uniform
{
public:
	float x;
	float y;
	
	Vector2 ();
	Vector2 (float x);
	Vector2 (float x, float y);
	Vector2 (IVector2 iv2);
	
	void UploadUniform (UniformID id);
	
	
	
	
	
	// Overloads
	
	// Vector comparison
	
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
	
	// Float comparison
	
	inline bool operator == (const float& rhs)
	{
		return x == rhs && y == rhs;
	}
	
	inline bool operator != (const float& rhs)
	{
		return x != rhs || y != rhs;
	}
	
	inline bool operator < (const float& rhs)
	{
		return x < rhs && y < rhs;
	}
	
	inline bool operator > (const float& rhs)
	{
		return x > rhs && y > rhs;
	}
	
	inline bool operator <= (const float& rhs)
	{
		return x <= rhs && y <= rhs;
	}
	
	inline bool operator >= (const float& rhs)
	{
		return x >= rhs && y >= rhs;
	}
	
	// Operator Math
	
	inline Vector2& operator += (const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	
	inline Vector2& operator -= (const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	
	inline Vector2& operator *= (const Vector2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	
	inline Vector2& operator /= (const Vector2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}
	
	
	inline Vector2& operator += (const float& rhs)
	{
		x += rhs;
		y += rhs;
		return *this;
	}
	
	inline Vector2& operator -= (const float& rhs)
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}
	
	inline Vector2& operator *= (const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	
	inline Vector2& operator /= (const float& rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	
	
	inline Vector2 operator + (const Vector2 rhs)
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}
	
	inline Vector2 operator - (const Vector2 rhs)
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}
	
	inline Vector2 operator * (const Vector2 rhs)
	{
		return Vector2(x * rhs.x, y * rhs.y);
	}
	
	inline Vector2 operator / (const Vector2 rhs)
	{
		return Vector2(x / rhs.x, y / rhs.y);
	}
	
	
};