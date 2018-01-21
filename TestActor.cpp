//
// Created by daniel on 1/20/2018.
//

#include "TestActor.h"

int TestActor::count = 0;

TestActor::TestActor ()
{
}

void TestActor::Tick ()
{
	float c = ((float)(PIx2 / count) * m) + time;
	transform.position = Vector2(sin(c), cos(c));
}

void TestActor::Render ()
{
	renderGroup->Add(transform.position);
}

void TestActor::OnCreated ()
{
	static RenderGroup<Vector2>* staticRenderGroup = new RenderGroup<Vector2>(Shapes::positionedQuad, 2, unitMaterial, world, 1000);
	renderGroup = staticRenderGroup;
	m = count;
	count++;
}

void TestActor::OnDestroyed ()
{
}
