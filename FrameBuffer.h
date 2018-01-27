
#pragma once

#include "Standard.h"
#include "Window.h"
#include "Texture.h"
#include "RenderBufferTexture.h"
#include "Color.h"
#include <vector>

HCLASS(FrameBuffer) : public Object
{
private:

public:
	
	int id = -1;
	
	HTexture colorBuffer;
	HTexture depthBuffer;
	
	const bool hasColorBuffer = false;
	const bool hasDepthBuffer = false;
	
	const bool fitWindow = false;
	
	const bool hdr = false;
	
	IVector2 pxSize;
	
	FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, bool fitWindow, bool hdr = false);
	FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, IVector2 size, bool hdr = false);
	explicit FrameBuffer (int id, bool hasColorBuffer = true, bool hasDepthBuffer = true, bool hdr = false);
	~FrameBuffer();
	
	
	bool IsGenerated ();
	bool IsDefaultFrameBuffer ();
	void OnWindowSizeChanged (HWindow window);
	void BindTo (unsigned int use);
	void BindDraw ();
	void BindRead ();
	void Use ();
	void Generate (IVector2 size);
	void Delete ();
	void Viewport (IVector2 resolution);
	void Clear (bool clearColorBuffer = true, bool clearDepthBuffer = true);
	void Clear (Color color, bool clearColorBuffer = true, bool clearDepthBuffer = true);
	
	static void Copy (HFrameBuffer fba, HFrameBuffer fbb, bool smooth = false, bool depth = false);
	static void Copy (HFrameBuffer fba, IVector2 fbaSize, HFrameBuffer fbb, bool smooth = false, bool depth = false);
};

extern HFrameBuffer defaultFrameBuffer;
extern HFrameBuffer currentFrameBuffer;


extern std::vector<HFrameBuffer> frameBuffers;