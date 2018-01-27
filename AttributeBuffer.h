#pragma once

#include "Standard.h"
#include <vector>

extern bool enabledAttributes[10];

enum class AttributeUsage : unsigned int
{
	PerVertex	= 0x88E0,
	PerDraw		= 0x88E4
};

HCLASS (AttributeBufferBase) : public Object
{
public:
	unsigned int attributeNumber;
	int elements = 0;
	
	virtual void Enable () = 0;
};

HCLASST(template<typename T>, T, AttributeBuffer) : public AttributeBufferBase
{
protected:
	
	unsigned int buffer;
	int dataSize;		// float : 4, vec4 : 16
	int dataElements;	// float : 1, vec2 : 2, vec4 : 4 etc...
	int attributeSpace;	// float : 1, vec4 : 1, mat2 : 2, mat4 : 4
	AttributeUsage usage;
	unsigned int divisor;
	bool constant;
public:
	
	AttributeBuffer (unsigned int attributeNumber, AttributeUsage usage, bool constant, int attributeTypeElements = 4);
	AttributeBuffer (unsigned int attributeNumber, AttributeUsage usage, bool constant, std::vector<T> data);
	
	void SetUsage (AttributeUsage usage);
	/// Uploads an array of data into the attribute buffer.
	/// @param data The array of data you want to upload.
	void UploadR (std::vector<T>& data);
	void Upload (std::vector<T> data);
	void Enable ();
	void Disable ();
};
