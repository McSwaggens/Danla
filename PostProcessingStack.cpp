//
// Created by daniel on 1/12/2018.
//

#include "PostProcessingStack.h"
#include "OpenGL.h"
#include "PostProcessing.h"

PostProcessingStack::PostProcessingStack ()
{

}

PostProcessingStack::PostProcessingStack (HFrameBuffer alphaBuffer, HFrameBuffer betaBuffer)
{
	this->alphaBuffer = alphaBuffer;
	this->betaBuffer = betaBuffer;
}

bool PostProcessingStack::Works ()
{
	return alphaBuffer && betaBuffer && effects.size() > 0;
}

HFrameBuffer PostProcessingStack::Process (HFrameBuffer sourceBuffer)
{
	bufferFlip = true;
	
	bool first = true;
	
	int totalIters = 0;
	
	HFrameBuffer primaryBuffer;
	HFrameBuffer secondaryBuffer;
	
	
	
	if (Works() && sourceBuffer)
	{
		for (auto effect : effects)
		{
			for (int iter = 0; iter < effect->iterations; iter++, totalIters++)
			{
				// Setup our primary and secondary buffers
				if (first)
				{
					first = false;
					
					primaryBuffer = sourceBuffer;
					secondaryBuffer = alphaBuffer;
				}
				else
				{
					primaryBuffer = (bufferFlip) ? alphaBuffer : betaBuffer;
					secondaryBuffer = (!bufferFlip) ? alphaBuffer : betaBuffer;
					
					bufferFlip = !bufferFlip;
				}
				
				PostProcess(primaryBuffer, secondaryBuffer, effect->GetMaterial());
				
			}
		}
		if (totalIters == 0)
		{
			return sourceBuffer;
		}
		else
		{
			return secondaryBuffer;
		}
	}
	
	return HFrameBuffer ();
}
