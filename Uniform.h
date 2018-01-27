#pragma once

#include <vector>
#include <ostream>

typedef int UniformID;


class Uniform
{
public:
	void UploadUniform (UniformID id);
};

typedef void (Uniform::*XFN_UploadUniform)(UniformID id);
