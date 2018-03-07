
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
	
	bool generated = false;
public:
	unsigned int id = UINT32_MAX;
	
	HTexture colorBuffer;
	HTexture hdrBuffer;
	HTexture depthBuffer;
	
	const bool hasColorBuffer = false;
	const bool hasDepthBuffer = false;
	
	const bool fitWindow = false;
	
	const bool hdr = false;
	
	IVector2 pxSize;
	
	FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, bool fitWindow, bool hdr = false);
	FrameBuffer (bool hasColorBuffer, bool hasDepthBuffer, IVector2 size, bool hdr = false);
	explicit FrameBuffer (unsigned int id, bool hasColorBuffer = true, bool hasDepthBuffer = true, bool hdr = false);
	~FrameBuffer();
	
	
	bool IsDefaultFrameBuffer ();
	void OnWindowSizeChanged (HWindow window);
	void BindTo (unsigned int use);
	void BindDraw ();
	void BindRead (unsigned int attachment = 0);
	void Use ();
	void Generate (IVector2 size);
	void Delete ();
	void Viewport (IVector2 resolution);
	void Clear (bool clearColorBuffer = true, bool clearDepthBuffer = true);
	void Clear (Color color, bool clearColorBuffer = true, bool clearDepthBuffer = true);
	void AttachColorBuffers ();
	std::vector<unsigned int> GetAttachments ();
	
	static void Copy (HFrameBuffer& fba, HFrameBuffer& fbb, bool smooth = false, bool depth = false, unsigned int attachment = 0);
	static void Copy (HFrameBuffer& fba, IVector2 fbaSize, HFrameBuffer& fbb, bool smooth = false, bool depth = false);
	static void CopyToDefaultFrameBuffer (HFrameBuffer& sourceBuffer);
};

extern HFrameBuffer defaultFrameBuffer;
extern HFrameBuffer currentFrameBuffer;


extern std::vector<HFrameBuffer> frameBuffers;