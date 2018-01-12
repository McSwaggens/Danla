
#pragma once

#include "Standard.h"
#include "AttributeBuffer.h"
#include <vector>



HCLASS(AttributeBatch) : public Object
{
private:
	bool DoesContainAttributeBufferID (int id);
public:
	bool enabled = false;
	std::vector<HAttributeBufferBase> buffers;
	
	AttributeBatch ();
	explicit AttributeBatch (std::vector<HAttributeBufferBase> _buffers);
	
	void Add (std::vector<HAttributeBufferBase> _buffers);
	void Enable ();
};



extern HAttributeBatch activeAttributeBatch;