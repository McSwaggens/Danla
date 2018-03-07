#pragma once

#include <stdint.h>
#include <stdio.h>

class HandleLink;
template<typename T>
class Handle;

#include "Object.h"

class HandleLink
{
public:
	int references;
	Object* object;
	
	HandleLink (Object& object);
	
	inline HandleLink (Object* object);
	inline void SoftUnlink ();
	
	inline void HardUnlink ();
	inline void AddReference ();
	
	inline void PopReference ();
};

inline HandleLink::HandleLink (Object* object)
{
	this->object = object;
	references = 0;
}

inline void HandleLink::AddReference ()
{
	references++;
}

inline void HandleLink::SoftUnlink ()
{
	object = 0;
}

inline void HandleLink::HardUnlink ()
{
	delete object;
	SoftUnlink ();
}

inline void HandleLink::PopReference ()
{
	references--;
	
	if (references == 0)
	{
		HardUnlink ();
	}
}

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
	inline void GhostDereference ();
	inline T* Get ();
	bool IsValid ();
	void Delete ();
	
	template<typename Other>
	inline Handle<Other>* CastTo ();
	
	inline T* operator->() const;
	inline Handle<T>& operator=(const Handle<T>& rh);
	inline Handle<T>& operator=(const Handle<T>* rh);
	
	bool operator==(const Handle<T>& rh);
	bool operator!=(const Handle<T>& rh);
	
	bool operator==(const T* rh);
	bool operator!=(const T* rh);
	
	bool operator==(const void* rh);
	bool operator!=(const void* rh);
	
	template<typename U>
	inline operator Handle<U> ();
	
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
	if (link)
	{
		link->AddReference ();
	}
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
inline T* Handle<T>::operator->() const
{
	return reinterpret_cast<T*>(link->object);
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
void Handle<T>::GhostDereference ()
{
	link->PopReference();
}

template<typename T>
template<typename Other>
inline Handle<Other>* Handle<T>::CastTo ()
{
	return (Handle<Other>*)(this);
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

template<typename T>
template<typename U>
Handle<T>::operator Handle<U> ()
{
	return reinterpret_cast<Handle<U>*>(this);
}
