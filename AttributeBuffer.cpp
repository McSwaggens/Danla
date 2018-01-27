#include "AttributeBuffer.h"
#include "OpenGL.h"
#include "Matrix4.h"

bool enabledAttributes[10] = { false };

template<typename T>
AttributeBuffer<T>::AttributeBuffer (unsigned int attributeNumber, AttributeUsage usage, bool constant, int attributeTypeElements)
{
	this->attributeNumber = attributeNumber;
	this->constant = constant;
	
	dataSize = sizeof(T);
	
	dataElements = dataSize / 4;
	attributeSpace = dataElements / attributeTypeElements;
	
	if (attributeSpace == 0)
	{
		attributeSpace = 1;
	}
	
	SetUsage (usage);
	
	glGenBuffers(1, &buffer);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
}

template<typename T>
AttributeBuffer<T>::AttributeBuffer (unsigned int attributeNumber, AttributeUsage usage, bool constant, std::vector<T> data) : AttributeBuffer (attributeNumber, usage, constant)
{
	Upload(data);
}

template<typename T>
void AttributeBuffer<T>::SetUsage (AttributeUsage usage)
{
	this->usage = usage;
	divisor = usage == AttributeUsage::PerVertex ? 0 : 1;
}

/*
 * TODO: Implement GL_DYNAMIC_DRAW, which indicates to the driver that it's going to be changed a lot.
 * 	We should also be using GL_STATIC_DRAW for vertex and UV buffer, it indicates to the driver that it's going to be written once and used A LOT.
 * 	Maybe use a "constant" bool value to choose?
 * 	enum?
 */

template<typename T>
void AttributeBuffer<T>::UploadR (std::vector<T>& data)
{
	elements = data.size();
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, (dataSize)*elements, &data[0], constant ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

template<typename T>
void AttributeBuffer<T>::Enable ()
{
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
	
	
	for (unsigned int attributeOffset = 0; attributeOffset < attributeSpace; attributeOffset++)
	{
		// An AttributeBatch should do this for the AttributeBuffer so there isn't any need for this
		// The code is still here for when you aren't using a AttributeBatch...
		// Which you should be...
		enabledAttributes[attributeNumber + attributeOffset] = true;
		
		glEnableVertexAttribArray(attributeNumber + attributeOffset);
		glVertexAttribPointer(attributeNumber + attributeOffset, dataElements / attributeSpace, GL_FLOAT, false, dataSize, (void*)(attributeOffset * (dataSize / attributeSpace)));
		glVertexAttribDivisor(attributeNumber + attributeOffset, divisor);
	}
	
	
}

template<typename T>
void AttributeBuffer<T>::Disable ()
{
	glDisableVertexAttribArray(attributeNumber);
	enabledAttributes[attributeNumber] = false;
}

template<typename T>
void AttributeBuffer<T>::Upload (std::vector<T> data)
{
	UploadR(data);
}

template class AttributeBuffer<Matrix2D>;
template class AttributeBuffer<Matrix4>;
template class AttributeBuffer<Vector2>;
template class AttributeBuffer<float>;
