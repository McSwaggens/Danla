//
// Created by daniel on 1/8/2018.
//

#include "RenderBufferTexture.h"
#include "OpenGL.h"

RenderBufferTexture::RenderBufferTexture ()
{
	glGenRenderbuffers(1, &id);
}

RenderBufferTexture::RenderBufferTexture (unsigned int id) : id (id)
{
}

void RenderBufferTexture::Bind ()
{
	glBindRenderbuffer(GL_RENDERBUFFER, id);
}

RenderBufferTexture::~RenderBufferTexture ()
{
	glDeleteRenderbuffers(1, &id);
}
