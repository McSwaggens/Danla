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
		
		bool newEnabledAttributes[10] = { false };
		
		for (int i = 0; i < buffers.size(); i++)
		{
			buffers[i]->Enable();
			newEnabledAttributes[buffers[i]->attributeNumber] = true;
		}
		
		enabled = true;
		
		// Make sure we disable any attributes that aren't needed.
		// We don't want the GPU to be fetching data it isn't even using...
		for (int i = 0; i < 10; i++)
		{
			if (enabledAttributes[i] && !newEnabledAttributes[i])
			{
				glDisableVertexAttribArray(i);
			}
		}
		
		std::copy(std::begin(newEnabledAttributes), std::end(newEnabledAttributes), std::begin(enabledAttributes));
	}
}



bool AttributeBatch::DoesContainAttributeBufferID (int id)
{
	for (HAttributeBufferBase attributeBufferBase : buffers)
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
