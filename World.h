//
// Created by daniel on 1/19/2018.
//

#pragma once

#include "Handle.h"
_HCLASS(World);

#include "Actor.h"
#include "SafeList.h"
#include "RenderGroup.h"
#include "Camera.h"


/*!
 *	@brief Contains all information regarding a level/scene
 *
 */
HCLASS(World) : public Object
{
private:

public:
	
	HCamera camera;
	SafeList<HActor> actors;
	std::vector<HRenderGroupBase> renderGroups;
	
	World ();
	void ComputeActors ();
	void Render ();
	void DispatchRenderGroups ();
	~World();
};


template<typename T>
inline Handle<T> Spawn (HWorld world)
{
	Handle<T> instance = new T();
	instance->world = world;
	world->actors.Add(instance);
	return instance;
}


template<typename T>
inline Handle<T> Spawn (HWorld world, T* t)
{
	Handle<T> instance (t);
	instance->world = world;
	world->actors.Add(instance);
	return instance;
}
