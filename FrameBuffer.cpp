//
// Created by daniel on 1/8/2018.
//


#include "FrameBuffer.h"
#include "Danla.h"
#include "OpenGL.h"

HFrameBuffer defaultFrameBuffer;
HFrameBuffer currentFrameBuffer;

FrameBuffer::FrameBuffer (int id, bool hasColorBuffer, bool hasDepthBuffer)
		: id(id), hasColorBuffer(hasColorBuffer), hasDepthBuffer(hasDepthBuffer)
{
	if (IsDefaultFrameBuffer())
	{
		pxSize = window->GetSize();
	}
}

bool FrameBuffer::IsGenerated ()
{
	return id != -1;
}

bool FrameBuffer::IsDefaultFrameBuffer ()
{
	return id == 0;
}

void FrameBuffer::Use ()
{
	if (IsGenerated())
	{
		BindTo(GL_DRAW_FRAMEBUFFER);
		currentFrameBuffer = this;
	}
}

void FrameBuffer::Delete ()
{
	glDeleteBuffers(1, (GLuint*)&id);
}

void FrameBuffer::Generate (Vector2 size)
{
	if (!IsDefaultFrameBuffer())
	{
		pxSize = size;
		
		if (id == -1)
		{
			glGenFramebuffers(1, (GLuint*)&id);
		}
		
		BindTo(GL_DRAW_FRAMEBUFFER);
		
		// Generate a color buffer
		if (colorBuffer.IsValid())
		{
			colorBuffer.Delete();
		}
		
		if (depthStencilBuffer.IsValid())
		{
			depthStencilBuffer.Delete();
		}
		
		
		colorBuffer = new Texture();
		depthStencilBuffer = new RenderBufferTexture();
		
		// Create Color Buffer
		
		colorBuffer->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)size.x, (int)size.y, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer->id, 0);
		
		// Create depth and stencil buffer
		
		depthStencilBuffer->Bind();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)size.x, (int)size.y);
		
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilBuffer->id);
		
		int status = glCheckFramebufferStatus (GL_FRAMEBUFFER);
		
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			Delete ();
			printf ("Couldn't create FrameBuffer.\nError code: %i", status);
		}
		
		// Bind the window's buffer.
		defaultFrameBuffer->Use();
	}
}

void FrameBuffer::OnWindowSizeChanged (HWindow window)
{
	if (fitWindow)
	{
	}
}

FrameBuffer::FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, bool fitWindow) : hasColorBuffer(
		hasColorBuffer), hasDepthBuffer(hasDepthBuffer), fitWindow(fitWindow)
{
	Generate (window->GetSize());
}

FrameBuffer::FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, Vector2 size) : hasColorBuffer(
		hasColorBuffer), hasDepthBuffer(hasDepthBuffer)
{
	Generate (size);
}



void FrameBuffer::BindTo (GLenum use)
{
	glBindFramebuffer (use, (GLuint)id);
}

FrameBuffer::~FrameBuffer ()
{
	Delete();
}

void FrameBuffer::BindDraw ()
{
	BindTo(GL_DRAW_FRAMEBUFFER);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void FrameBuffer::BindRead ()
{
	BindTo(GL_READ_FRAMEBUFFER);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	colorBuffer->Bind();
}

void FrameBuffer::Copy (HFrameBuffer fba, HFrameBuffer fbb)
{
	fba->BindRead();
	fbb->BindDraw();
	
	glBlitFramebuffer
	(
			0, 0, static_cast<GLint>(fba->pxSize.x), static_cast<GLint>(fba->pxSize.y),
			0, 0, static_cast<GLint>(fbb->pxSize.x), static_cast<GLint>(fbb->pxSize.y),
			GL_COLOR_BUFFER_BIT, GL_LINEAR
	);
}

