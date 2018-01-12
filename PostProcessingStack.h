//
// Created by daniel on 1/12/2018.
//

#pragma once

#include "Danla.h"
#include "Effect.h"
#include "FrameBuffer.h"
#include <vector>

HCLASS(PostProcessingStack) : Object
{
private:
	
	bool Works ();
	
	HFrameBuffer alphaBuffer;
	HFrameBuffer betaBuffer;
	
	bool bufferFlip = false;
	
public:
	std::vector<HEffectBase> effects;
	
	
	PostProcessingStack ();
	/// Hello World
	/// @param alphaBuffer
	/// @param betaBuffer
	PostProcessingStack (HFrameBuffer alphaBuffer, HFrameBuffer betaBuffer);
	
	/// Applies all effects attached to this PostProcessingStack.
	/// @param sourceBuffer The FrameBuffer that contains what you want to apply the effects too.
	/// @returns The resulting framebuffer with all effects applied.
	HFrameBuffer Process (HFrameBuffer sourceBuffer);
};



