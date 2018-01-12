
#pragma once

#include "Standard.h"
#include "Window.h"
#include "Texture.h"
#include "RenderBufferTexture.h"

HCLASS(FrameBuffer) : public Object
{
private:

public:
	
	int id = -1;
	
	HTexture colorBuffer;
	HRenderBufferTexture depthStencilBuffer;
	
	const bool hasColorBuffer = false;
	const bool hasDepthBuffer = false;
	const bool hasStencilBuffer = false;
	
	const bool fitWindow = false;
	
	Vector2 pxSize;
	
	FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, bool fitWindow);
	FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, Vector2 size);
	FrameBuffer (int id, bool hasColorBuffer = true, bool hasDepthBuffer = true);
	~FrameBuffer();
	
	
	bool IsGenerated ();
	bool IsDefaultFrameBuffer ();
	void OnWindowSizeChanged (HWindow window);
	void BindTo (unsigned int use);
	void BindDraw ();
	void BindRead ();
	void Use ();
	void Generate (Vector2 size);
	void Delete ();
	
	static void Copy (HFrameBuffer fba, HFrameBuffer fbb);
};

extern HFrameBuffer defaultFrameBuffer;
extern HFrameBuffer currentFrameBuffer;
