//
// Created by daniel on 1/14/2018.
//


#include "PostProcessing.h"
#include "FrameBuffer.h"
#include "Material.h"

void PostProcess (HFrameBuffer alphaBuffer, HFrameBuffer betaBuffer, HPostProcessorMaterial material)
{
	alphaBuffer->BindRead();
	betaBuffer->BindDraw();
	
	betaBuffer->Clear();
	
	material->u_InputTexture = alphaBuffer->colorBuffer;
	
	material->Enable();
	
	DrawShape(Shapes::quad);
}
