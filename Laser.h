//
// Created by daniel on 1/28/2018.
//

#pragma once

#include "Danla.h"


MATERIAL(LaserMaterial)
END_MATERIAL;

extern HLaserMaterial laserMaterial;

HCLASS(Laser) : public Actor
{
private:

public:
	
	HRenderGroup<Matrix4> renderGroup;
	
	Laser ();
	
	void Render () override;
	
	void Tick () override;
	
	void OnCreated () override;
	
	void OnDestroyed () override;
};



