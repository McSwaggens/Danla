#pragma once

#include <stdint.h>
#include <string>

#define ONCE(x) static bool __b_##__COUNTER__ = true; if (__b_##__COUNTER__) { __b_##__COUNTER__ = false; x; }

typedef std::string String;
typedef char* CString;

//inline void* operator new (size_t sz)
//{
//	if (sz > 1024)
//	{
//		printf ("Allocating %i bytes of memory.\n", sz);
//	}
//
//	void* ptr = malloc(sz);
//	return ptr;
//}

#include "Handle.h"
#include "Object.h"
#include "Uniform.h"
#include "Shader.h"
#include "Vector2.h"
#include "Vector3.h"
#include "IVector2.h"
#include "Matrix4.h"
#include "Matrix2D.h"
#include "Transform.h"
