//
// Created by daniel on 1/20/2018.
//

#include "TestActor.h"
#include <cstring>
#include "OpenGL.h"
#include "Input.h"

int TestActor::count = 0;
int TestActor::rendered = 0;

TestActor::TestActor ()
{
}

void TestActor::Tick ()
{

	
//	float change = IsKeyDown(Keys::Q) ? 1.0f : IsKeyDown(Keys::E) ? -1.0f : 0.0f;
//	transform.rotation += change * logicDelta;
}

void TestActor::Render ()
{
	if (!activeCamera->IsCulled(transform))
	{
		renderGroup->Add(transform.GetMatrix());
		rendered++;
	}
}

void TestActor::OnCreated ()
{
	static RenderGroup<Matrix4>* staticRenderGroup = new RenderGroup<Matrix4>(Shapes::matrixQuad, 2, unitMaterial, world, 1000);
	renderGroup = staticRenderGroup;
	m = count;
	count++;
	
	transform.position = (Vector2((sin(m) * m) / (5.0f), (cos(m) * m) / 5.0f));
}

void TestActor::OnDestroyed ()
{
}

TestActor::TestActor (Vector2 position)
{

}
