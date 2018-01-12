#include "Buffer.h"
#include "OpenGL.h"

Buffer::Buffer ()
{
	glGenBuffers(1, &buffer);
}

Buffer::Buffer (unsigned int _buffer)
{
	buffer = _buffer;
}

void Buffer::Bind ()
{
	glBindBuffer(GL_VERTEX_ARRAY, buffer);
}

void Buffer::Bind (int target)
{
	glBindBuffer(target, buffer);
}

