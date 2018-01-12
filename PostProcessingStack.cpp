//
// Created by daniel on 1/12/2018.
//

#include "PostProcessingStack.h"
#include "OpenGL.h"

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
	return alphaBuffer && betaBuffer && effects.size();
}

HFrameBuffer PostProcessingStack::Process (HFrameBuffer sourceBuffer)
{
	bufferFlip = false;
	
	bool first = true;
	
	HFrameBuffer primaryBuffer;
	HFrameBuffer secondaryBuffer;
	
	
	if (Works() && sourceBuffer)
	{
		for (auto effect : effects)
		{
			for (int iter = 0; iter < effect->iterations; iter++)
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
				
				primaryBuffer->BindRead();
				secondaryBuffer->BindDraw();
				
				effect->Use();
				
				DrawShape(Shapes::quad);
				
			}
		}
	}
	
	return HFrameBuffer ();
}
