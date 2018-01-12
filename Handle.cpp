#include "Handle.h"


// HandleLink

HandleLink::HandleLink (Object* object)
{
	this->object = object;
	references = 0;
}

void HandleLink::AddReference ()
{
	references++;
	// printf ("Add! refs = %i\n", references);
}

void HandleLink::SoftUnlink ()
{
	object = 0;
}

void HandleLink::HardUnlink ()
{
	delete object;
	SoftUnlink ();
}

void HandleLink::PopReference ()
{
	references--;
	
	// printf ("Pop! refs = %i\n", references);
	
	if (!references)
	{
		//printf ("At hard unlink!\n");
		HardUnlink ();
	}
}

