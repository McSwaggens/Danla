//
// Created by daniel on 1/28/2018.
//

#include "Laser.h"

HLaserMaterial laserMaterial;

Laser::Laser ()
{
}

void Laser::Render ()
{
	if (!activeCamera->IsCulled(transform))
	{
		renderGroup->Add(transform.GetMatrix());
	}
}

void Laser::Tick ()
{
}

void Laser::OnCreated ()
{
	static RenderGroup<Matrix4>* staticRenderGroup = new RenderGroup<Matrix4>(Shapes::matrixQuad, 2, laserMaterial, world, 1000);
	renderGroup = staticRenderGroup;
	
	transform.SetScale(Vector2(0.1f, 0.3f));
}

void Laser::OnDestroyed ()
{
}
