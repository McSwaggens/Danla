//
// Created by daniel on 1/20/2018.
//

#pragma once

#include "Danla.h"

HCLASS(TestActor) : public Actor
{
public:
	HRenderGroup<Matrix4> renderGroup;
	
	static int count;
	static int rendered;
	
	float m = 0;
	TestActor ();
	TestActor (Vector2 position);
	
	void Render () override;
	
	void Tick () override;
	
	void OnCreated () override;
	
	void OnDestroyed () override;
};



