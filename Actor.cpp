//
// Created by daniel on 1/19/2018.
//

#include "Actor.h"

Actor::Actor ()
{
}

void Actor::Destroy ()
{
	//TODO: Remove Actor from world.
	world->actors.Remove(this);
}

void Actor::Render ()
{
}
