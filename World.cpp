//
// Created by daniel on 1/19/2018.
//

#include "World.h"

World::World ()
{
	
}

World::~World ()
{
	actors.values.clear();
}

void World::ComputeActors ()
{
	static std::vector<HActor> lastRemoveStack;
	static std::vector<HActor> lastAddStack;
	
	if (lastRemoveStack.size() > 0)
	{
		for (auto actor : lastRemoveStack)
		{
			actor->OnDestroyed();
		}
		
		lastRemoveStack.clear();
	}
	
	if (lastAddStack.size() > 0)
	{
		for (auto actor : lastAddStack)
		{
			actor->SetEnabled(true);
			actor->OnCreated();
		}
		
		lastAddStack.clear();
	}
	
	std::vector<HActor>& _actors = actors.values;
	for (int i = 0; i < _actors.size(); i++)
	{
		HActor& actor = _actors[i];
		if (actor->IsEnabled())
		{
			actor->Tick();
		}
	}
	
	lastAddStack.insert(lastAddStack.end(), actors.addStack.begin(), actors.addStack.end());
	lastRemoveStack.insert(lastRemoveStack.end(), actors.removeStack.begin(), actors.removeStack.end());
	
	actors.Sort();
}

void World::DispatchRenderGroups ()
{
	for (auto renderGroup : renderGroups)
	{
		renderGroup->Render();
	}
}

void World::Render ()
{
	camera->PreComputeMatrix();
	
	std::vector<HActor>& _actors = actors.values;
	for (int i = 0; i < _actors.size(); i++)
	{
		HActor& actor = _actors[i];
		if (actor->IsEnabled())
		{
			actor->Render();
		}
	}
	
	camera->RenderWorld(this);
}

void AddRenderGroupToWorld (HRenderGroupBase renderGroup, HWorld world)
{
	world->renderGroups.push_back (renderGroup);
}
