#include "AttributeBuffer.h"
#include "OpenGL.h"

bool enabledAttributes[10] = { false };

template<typename T>
AttributeBuffer<T>::AttributeBuffer (int attributeNumber, AttributeUsage usage)
{
	this->attributeNumber = attributeNumber;
	
	dataSize = sizeof(T);
	
	if (dataSize % 4 == 0)
	{
		dataElements = dataSize / 4;
	}
	else
	{
		printf ("Cannot divide AttributeBuffer type by 4, invalid type used.\n");
		return;
	}
	
	SetUsage (usage);
	
	glGenBuffers(1, &buffer);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
}

template<typename T>
void AttributeBuffer<T>::SetUsage (AttributeUsage usage)
{
	this->usage = usage;
	divisor = usage == AttributeUsage::PerVertex ? 0 : 1;
}

template<typename T>
void AttributeBuffer<T>::Upload (std::vector<T> data)
{
	elements = data.size();
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, (dataSize)*elements, &data[0], GL_STREAM_DRAW);
}

template<typename T>
void AttributeBuffer<T>::Enable ()
{
	// An AttributeBatch should do this for the AttributeBuffer so there isn't any need for this
	// The code is still here for when you aren't using a AttributeBatch...
	// Which you should be...
	enabledAttributes[attributeNumber] = true;
	
	glEnableVertexAttribArray(attributeNumber);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(attributeNumber, dataElements, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(attributeNumber, divisor);
}

template<typename T>
void AttributeBuffer<T>::Disable ()
{
	glDisableVertexAttribArray(attributeNumber);
	enabledAttributes[attributeNumber] = false;
}

template<typename T>
AttributeBuffer<T>::AttributeBuffer (int attributeNumber, AttributeUsage usage, std::vector<T> data) : AttributeBuffer (attributeNumber, usage)
{
	Upload(data);
}

template class AttributeBuffer<Vector2>;
template class AttributeBuffer<float>;