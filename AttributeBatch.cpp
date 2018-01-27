//
// Created by daniel on 1/6/2018.
//


#include "AttributeBatch.h"
#include <stdarg.h>
#include "OpenGL.h"

HAttributeBatch activeAttributeBatch;

void AttributeBatch::Add (std::vector<HAttributeBufferBase> _buffers)
{
	for (HAttributeBufferBase attributeBufferBase : _buffers)
	{
		if (!DoesContainAttributeBufferID(attributeBufferBase->attributeNumber))
		{
			buffers.push_back(attributeBufferBase);
		}
		else
		{
			printf ("Attribute already assigned to AttributeBatch.\n");
		}
	}
}

void AttributeBatch::Enable ()
{
	if (!enabled)
	{
		if (activeAttributeBatch.Get() == NULL)
		{
			activeAttributeBatch = this;
		}
		else
		if (activeAttributeBatch.Get() == (AttributeBatch*)(link->object))
		{
			return;
		}
		
		activeAttributeBatch->enabled = false;
		
		activeAttributeBatch = this;
		
		bool oldEnabledAttributes[10] = { false };
		std::copy(std::begin(enabledAttributes), std::end(enabledAttributes), std::begin(oldEnabledAttributes));
		memset(enabledAttributes, 0, sizeof(enabledAttributes));
		
		for (int i = 0; i < buffers.size(); i++)
		{
			buffers[i]->Enable();
		}
		
		enabled = true;
		
		// Make sure we disable any attributes that aren't needed.
		// We don't want the GPU to be fetching data it isn't even using...
		for (int i = 0; i < 10; i++)
		{
			if (!enabledAttributes[i] && oldEnabledAttributes[i])
			{
				glDisableVertexAttribArray(i);
			}
		}
	}
}



bool AttributeBatch::DoesContainAttributeBufferID (int id)
{
	for (HAttributeBufferBase& attributeBufferBase : buffers)
	{
		if (attributeBufferBase->attributeNumber == id)
		{
			return true;
		}
	}
	
	return false;
}

AttributeBatch::AttributeBatch (std::vector<HAttributeBufferBase> _buffers)
{
	Add(_buffers);
}

AttributeBatch::AttributeBatch ()
{
}

bool AttributeBatch::GetBufferWithAttributeID (int id, HandleLink*& attributeBufferBase)
{
	for (HAttributeBufferBase& _attributeBufferBase : buffers)
	{
		if (_attributeBufferBase->attributeNumber == id)
		{
			attributeBufferBase = _attributeBufferBase.link;
			return true;
		}
	}
	
	return false;
}
