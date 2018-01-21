//
// Created by daniel on 1/20/2018.
//

#pragma once

#include "Danla.h"

HCLASS(TestActor) : public Actor
{
public:
	HRenderGroup<Vector2> renderGroup;
	
	static int count;
	
	float m = 0;
	TestActor ();
	
	void Render () override;
	
	void Tick () override;
	
	void OnCreated () override;
	
	void OnDestroyed () override;
};



