#pragma once

#include <stdint.h>
#include <string>

#define ONCE(x) static bool __b_##__COUNTER__ = true; if (__b_##__COUNTER__) { __b_##__COUNTER__ = false; x; }

typedef std::string String;
typedef char* CString;

#include "Handle.h"
#include "Object.h"
#include "Uniform.h"
#include "Shader.h"
#include "Vector2.h"
#include "IVector2.h"
