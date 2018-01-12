#pragma once

#include "Standard.h"
#include <vector>

struct ShaderSource
{
	String code;
	int type;
};

std::vector<ShaderSource> PreProcess (String source);