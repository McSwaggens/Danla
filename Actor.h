//
// Created by daniel on 1/19/2018.
//

#pragma once

#include "Handle.h"
_HCLASS(Actor);

#include "Entity.h"
#include "World.h"
#include "Transform.h"

/*!
 *
 *	@brief An Actor is an Object that lives inside of the game world.
 *	@brief it has a transform (position, scale, rotation), World Handle and more.
 *
 *
 *	@note Anything that isn't pure logic code should be an actor.
 *	@note An actor isn't required to render anything to the screen but will belong to a single world.
 *
 */
HCLASS(Actor) : public Entity
{
private:
public:
	
	Transform transform;
	
	HWorld world;
	
	Actor ();
	virtual void Render ();
	void Destroy () override;
};
