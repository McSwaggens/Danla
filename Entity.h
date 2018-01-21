//
// Created by daniel on 1/19/2018.
//

#pragma once

#include "Standard.h"

/*!
 *
 *	@brief An Entity is the base game engine logic class.
 *
 */
HCLASS(Entity) : Object
{
private:
	
	bool enabled = false;
	
public:
	Entity ();
	~Entity ();
	
	virtual void Tick () = 0;
	virtual void Destroy () = 0;
	virtual void OnCreated () = 0;
	virtual void OnDestroyed () = 0;
	
	inline bool IsEnabled ()
	{
		return enabled;
	}
	
	inline void SetEnabled (bool _enabled)
	{
		enabled = _enabled;
	}
};


