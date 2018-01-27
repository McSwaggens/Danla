//
// Created by daniel on 1/8/2018.
//


#include "FrameBuffer.h"
#include "Danla.h"
#include "OpenGL.h"

HFrameBuffer defaultFrameBuffer;
HFrameBuffer currentFrameBuffer;

std::vector<HFrameBuffer> frameBuffers;

FrameBuffer::FrameBuffer (int id, bool hasColorBuffer, bool hasDepthBuffer, bool hdr)
		: id(id), hasColorBuffer(hasColorBuffer), hasDepthBuffer(hasDepthBuffer), hdr(!IsDefaultFrameBuffer() && hdr)
{
	if (IsDefaultFrameBuffer())
	{
		pxSize = window->GetSize();
	}
	
	frameBuffers.push_back(this);
}

FrameBuffer::FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, bool fitWindow, bool hdr) : hasColorBuffer(
		hasColorBuffer), hasDepthBuffer(hasDepthBuffer), fitWindow(fitWindow), hdr(hdr)
{
	frameBuffers.push_back(this);
	Generate (window->GetSize());
}

FrameBuffer::FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, IVector2 size, bool hdr) : hasColorBuffer(
		hasColorBuffer), hasDepthBuffer(hasDepthBuffer), hdr(hdr)
{
	frameBuffers.push_back(this);
	Generate (size);
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
	if (!IsDefaultFrameBuffer())
	{
		glDeleteFramebuffers(1, (GLuint*)&id);
		id = -1;
		
		if (colorBuffer)
		{
			colorBuffer.Delete();
		}
		if (depthBuffer)
		{
			depthBuffer.Delete();
		}
	}
}

void FrameBuffer::Generate (IVector2 size)
{
	if (!IsDefaultFrameBuffer())
	{
		pxSize = size;
		
		if (id == -1)
		{
			glGenFramebuffers(1, (GLuint*)&id);
		}
		
		BindTo(GL_FRAMEBUFFER);
		
		// Generate a color buffer
		if (hasColorBuffer && colorBuffer.IsValid())
		{
			colorBuffer.Delete();
		}
		
		if (hasDepthBuffer && depthBuffer.IsValid())
		{
			depthBuffer.Delete();
		}
		
		
		if (hasColorBuffer)
		{
			colorBuffer = new Texture();
			colorBuffer->Bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, hdr ? GL_FLOAT : GL_BYTE, 0);
			colorBuffer->SetInterpolationLinear();
			colorBuffer->EdgeClamp(true, true);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer->id, 0);
		}
		
		if (hasDepthBuffer)
		{
			depthBuffer = new Texture();
			depthBuffer->Bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, size.x, size.y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);
			depthBuffer->SetInterpolationNearest();
			depthBuffer->ClampMirror(true, true);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthBuffer->id, 0);
		}
		
		int status = glCheckFramebufferStatus (GL_FRAMEBUFFER);
		
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			Delete ();
			printf ("Couldn't create FrameBuffer.\nError code: %i\n", status);
		}
		
		// Bind the window's buffer.
		defaultFrameBuffer->Use();
	}
}

void FrameBuffer::OnWindowSizeChanged (HWindow window)
{
	if (IsDefaultFrameBuffer())
	{
		pxSize = window->GetSize();
	}
	else if (fitWindow)
	{
		Delete();
		Generate(window->GetSize());
	}
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
	glDrawBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
	
	if (hasDepthBuffer)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
	}
	
	glViewport(0, 0, pxSize.x, pxSize.y);
}

void FrameBuffer::BindRead ()
{
	BindTo(GL_READ_FRAMEBUFFER);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	colorBuffer->Bind(0);
	
	glViewport(0, 0, pxSize.x, pxSize.y);
}

void FrameBuffer::Copy (HFrameBuffer fba, HFrameBuffer fbb, bool smooth, bool depth)
{
	fba->BindRead();
	fbb->BindDraw();
	
	glBlitFramebuffer
	(
			0, 0, fba->pxSize.x, fba->pxSize.y,
			0, 0, fbb->pxSize.x, fbb->pxSize.y,
			GL_COLOR_BUFFER_BIT, smooth ? GL_LINEAR : GL_NEAREST
	);
	
	if (depth)
	{
		glBlitFramebuffer
		(
				0, 0, fba->pxSize.x, fba->pxSize.y,
				0, 0, fbb->pxSize.x, fbb->pxSize.y,
				GL_DEPTH_BUFFER_BIT, smooth ? GL_LINEAR : GL_NEAREST
		);
	}
}

void FrameBuffer::Copy (HFrameBuffer fba, IVector2 fbaSize, HFrameBuffer fbb, bool smooth, bool depth)
{
	fba->BindRead();
	fbb->BindDraw();
	
	glBlitFramebuffer
	(
			0, 0, fbaSize.x, fbaSize.y,
			0, 0, fbb->pxSize.x, fbb->pxSize.y,
			GL_COLOR_BUFFER_BIT, smooth ? GL_LINEAR : GL_NEAREST
	);
	
	if (depth)
	{
		glBlitFramebuffer
		(
				0, 0, fbaSize.x, fbaSize.y,
				0, 0, fbb->pxSize.x, fbb->pxSize.y,
				GL_DEPTH_BUFFER_BIT, smooth ? GL_LINEAR : GL_NEAREST
		);
	}
}

void FrameBuffer::Clear (Color color, bool clearColorBuffer, bool clearDepthBuffer)
{
	glClearColor (color.r, color.g, color.b, color.a);
	Clear (clearColorBuffer, clearDepthBuffer);
}

void FrameBuffer::Clear (bool clearColorBuffer, bool clearDepthBuffer)
{
	GLbitfield mask = 0;
	if (clearColorBuffer)
	{
		(mask) |= (GL_COLOR_BUFFER_BIT);
	}
	if (clearDepthBuffer)
	{
		(mask) |= (GL_DEPTH_BUFFER_BIT);
	}
	
	glClear(mask);
}

void FrameBuffer::Viewport (IVector2 resolution)
{
	BindTo(GL_FRAMEBUFFER);
	glViewport(0, 0, resolution.x, resolution.y);
}

