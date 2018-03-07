//
// Created by daniel on 1/8/2018.
//


#include "FrameBuffer.h"
#include "Danla.h"
#include "OpenGL.h"

HFrameBuffer defaultFrameBuffer;
HFrameBuffer currentFrameBuffer;

std::vector<HFrameBuffer> frameBuffers;

FrameBuffer::FrameBuffer (unsigned int id, bool hasColorBuffer, bool hasDepthBuffer, bool hdr)
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

bool FrameBuffer::IsDefaultFrameBuffer ()
{
	return id == 0;
}

void FrameBuffer::Use ()
{
	if (generated)
	{
		BindTo(GL_DRAW_FRAMEBUFFER);
		currentFrameBuffer = this;
	}
}

void FrameBuffer::Delete ()
{
	if (!IsDefaultFrameBuffer())
	{
		glDeleteFramebuffers(1, &id);
		id = UINT32_MAX;
		generated = false;
		
		if (colorBuffer)
		{
			colorBuffer.Delete();
		}
		if (depthBuffer)
		{
			depthBuffer.Delete();
		}
		if (hdr)
		{
			hdrBuffer.Delete();
		}
	}
}

void FrameBuffer::Generate (IVector2 size)
{
	if (!IsDefaultFrameBuffer())
	{
		pxSize = size;
		
		if (!generated)
		{
			glGenFramebuffers(1, &id);
		}
		
		BindTo(GL_FRAMEBUFFER);
		
		if (hasColorBuffer && colorBuffer.IsValid())
		{
			colorBuffer.Delete();
		}
		
		if (hdr && hdrBuffer.IsValid())
		{
			hdrBuffer.Delete();
		}
		
		if (hasDepthBuffer && depthBuffer.IsValid())
		{
			depthBuffer.Delete();
		}
		
		if (hasColorBuffer)
		{
			colorBuffer = new Texture();
			colorBuffer->Bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, size.x, size.y, 0, GL_RGB, GL_FLOAT, 0);
			colorBuffer->SetInterpolationLinear();
			colorBuffer->EdgeClamp(true, true);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer->id, 0);
			PrintErrors ();
		}
		
		if (hdr)
		{
			hdrBuffer = new Texture();
			hdrBuffer->Bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, size.x, size.y, 0, GL_RGB, GL_FLOAT, 0);
			hdrBuffer->SetInterpolationLinear();
			hdrBuffer->EdgeClamp(true, true);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, hdrBuffer->id, 0);
			PrintErrors ();
		}
		
		if (hasDepthBuffer)
		{
			depthBuffer = new Texture();
			depthBuffer->Bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, size.x, size.y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);
			depthBuffer->SetInterpolationNearest();
			depthBuffer->ClampMirror(true, true);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthBuffer->id, 0);
			PrintErrors ();
		}
		
		generated = true;
		
		int status = glCheckFramebufferStatus (GL_FRAMEBUFFER);
		
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			Delete ();
			printf ("Couldn't create FrameBuffer.\nError code: %i\n", status);
			generated = false;
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
	glBindFramebuffer (use, id);
}

FrameBuffer::~FrameBuffer ()
{
	Delete();
}

void FrameBuffer::BindDraw ()
{
	BindTo(GL_DRAW_FRAMEBUFFER);
	AttachColorBuffers();
}

void FrameBuffer::BindRead (unsigned int attachment)
{
	BindTo(GL_READ_FRAMEBUFFER);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment);
}

void FrameBuffer::Copy (HFrameBuffer& fba, HFrameBuffer& fbb, bool smooth, bool depth, unsigned int attachment)
{
	fba->BindRead(attachment);
	fbb->BindDraw();
	
	IVector2 sourceSize = fba->pxSize;
	IVector2 destinationSize = fbb->pxSize;
	
	glBlitFramebuffer
	(
			0, 0, sourceSize.x, sourceSize.y,
			0, 0, destinationSize.x, destinationSize.y,
			GL_COLOR_BUFFER_BIT, smooth ? GL_LINEAR : GL_NEAREST
	);
	
//	if (depth)
//	{
//		glBlitFramebuffer
//		(
//				0, 0, fba->pxSize.x, fba->pxSize.y,
//				0, 0, fbb->pxSize.x, fbb->pxSize.y,
//				GL_DEPTH_BUFFER_BIT, smooth ? GL_LINEAR : GL_NEAREST
//		);
//	}
}

void FrameBuffer::Copy (HFrameBuffer& fba, IVector2 fbaSize, HFrameBuffer& fbb, bool smooth, bool depth)
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
	
	if (hdr)
	{
		static const float clearColor[] = { 0, 0, 0 };
		glClearBufferfv(GL_COLOR, 1, clearColor);
	}
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

std::vector<unsigned int> FrameBuffer::GetAttachments ()
{
	std::vector<unsigned int> attachments;
	
	if (hasColorBuffer)
	{
		attachments.push_back(GL_COLOR_ATTACHMENT0);
	}
	
	if (hdr)
	{
		attachments.push_back(GL_COLOR_ATTACHMENT1);
	}
	
	if (hasDepthBuffer)
	{
		attachments.push_back(GL_DEPTH_STENCIL_ATTACHMENT);
	}
	
	return attachments;
}

void FrameBuffer::AttachColorBuffers ()
{
	if (hdr)
	{
		static const GLenum attachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);
	}
	else
	{
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}
}

void FrameBuffer::CopyToDefaultFrameBuffer (HFrameBuffer& sourceBuffer)
{
	sourceBuffer->BindRead();
	defaultFrameBuffer->BindTo(GL_DRAW_FRAMEBUFFER);
	
	glBlitFramebuffer
	(
			0, 0, sourceBuffer->pxSize.x, sourceBuffer->pxSize.y,
			0, 0, defaultFrameBuffer->pxSize.x, defaultFrameBuffer->pxSize.y,
			GL_COLOR_BUFFER_BIT, GL_NEAREST
	);
}

