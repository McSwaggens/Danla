//
// Created by daniel on 1/14/2018.
//

#pragma once

#include "Danla.h"
#include "FrameBuffer.h"
#include "Material.h"


MATERIAL(PostProcessorMaterial)
	TEXTURE(u_InputTexture, 0);
	TEXTURE(u_DepthTexture, 1);
END_MATERIAL;

void PostProcess (HFrameBuffer alphaBuffer, HFrameBuffer betaBuffer, HPostProcessorMaterial material);