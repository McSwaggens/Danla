#pragma once

#include <stdint.h>
#include "Standard.h"

class HandleLink;
template<typename T>
class Handle;

#include "Object.h"

class HandleLink
{
public:
	int references;
	
	HandleLink (Object& object);
	HandleLink (Object* object);
	
	void SoftUnlink ();
	void HardUnlink ();
	
	void AddReference ();
	void PopReference ();
	
	Object* object;
};

template<typename T>
class Handle
{
public:
	HandleLink* link = 0;
	
	Handle ();
	Handle (const Handle<T>& handle);
	Handle (const Handle<T>* handle);
	Handle (const T* object);
	~Handle ();
	
	inline void Dereference ();
	inline T* Get ();
	bool IsValid ();
	void Delete ();
	
	template<typename Other>
	Handle<Other> CastTo ();
	
	inline T* operator->();
	inline Handle<T>& operator=(const Handle<T>& rh);
	inline Handle<T>& operator=(const Handle<T>* rh);
	
	bool operator==(const Handle<T>& rh);
	bool operator!=(const Handle<T>& rh);
	
	bool operator==(const T* rh);
	bool operator!=(const T* rh);
	
	bool operator==(const void* rh);
	bool operator!=(const void* rh);
	
	inline explicit operator bool() const;
	inline operator bool ();
};

// Handle

template<typename T>
Handle<T>::Handle ()
{
}

template<typename T>
Handle<T>::Handle (const Handle<T>& handle)
{
	link = handle.link;
	link->AddReference ();
}

template<typename T>
Handle<T>::Handle (const Handle<T>* handle)
{
	link = handle->link;
	link->AddReference ();
}

template<typename T>
Handle<T>::Handle (const T* object)
{
	link = ((Object*)object)->link;
	link->AddReference ();
}

template<typename T>
Handle<T>::~Handle ()
{
	if (link)
	{
		link->PopReference();
	}
}

template<typename T>
inline T* Handle<T>::operator->()
{
	return (T*)link->object;
}

template<typename T>
inline T* Handle<T>::Get()
{
	if (link == NULL)
	{
		return NULL;
	}
	
	return (T*)link->object;
}

template<typename T>
inline Handle<T>& Handle<T>::operator=(const Handle<T>& handle)
{
	if (link != handle.link)
	{
		if (link)
		{
			link->PopReference();
		}
		link = handle.link;
		link->AddReference();
	}
	
	return *this;
}

template<typename T>
inline Handle<T>& Handle<T>::operator=(const Handle<T>* handle)
{
	if (link != handle->link)
	{
		if (link)
		{
			link->PopReference();
		}
		
		link = handle->link;
		link->AddReference();
	}
	
	return *this;
}


template<typename T>
inline void Handle<T>::Dereference ()
{
	link->PopReference();
	link = 0;
}

template<typename T>
template<typename Other>
Handle<Other> Handle<T>::CastTo ()
{
	return Handle<Other>((const Other*)link->object);
}

template<typename T>
bool Handle<T>::IsValid ()
{
	return link != NULL && link->object != NULL;
}

template<typename T>
void Handle<T>::Delete ()
{
	link->HardUnlink();
	Dereference();
}

template<typename T>
bool Handle<T>::operator== (const Handle<T>& rh)
{
	if (rh.link == NULL || link == NULL)
	{
		return false;
	}
	
	return link->object == rh.link->object;
}

template<typename T>
bool Handle<T>::operator!= (const Handle<T>& rh)
{
	return !(this == rh);
}

template<typename T>
bool Handle<T>::operator== (const T* rh)
{
	if (link == NULL)
	{
		return false;
	}
	
	return link->object == (Object*)rh;
}

template<typename T>
bool Handle<T>::operator!= (const T* rh)
{
	return !(this == rh);
}

template<typename T>
bool Handle<T>::operator== (const void* rh)
{
	if (link == NULL)
	{
		return false;
	}
	
	return link->object == rh;
}

template<typename T>
bool Handle<T>::operator!= (const void* rh)
{
	return !(this == rh);
}

template<typename T>
inline Handle<T>::operator bool () const
{
	return (link != NULL && link->object != NULL);
}

template<typename T>
inline Handle<T>::operator bool ()
{
	return (link != NULL && link->object != NULL);
}
