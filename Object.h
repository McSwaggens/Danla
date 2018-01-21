#pragma once

#define DEFHCLASS(c) using H##c = Handle<c>
#define _HCLASS(c) class c; DEFHCLASS(c);
#define HCLASS(c) _HCLASS(c); class c

#define DEFHCLASST(d, n, c) d using H##c = Handle<c<n>>
#define _HCLASST(d, n, c) d class c; DEFHCLASST(d, n, c);
#define HCLASST(d, n, c) _HCLASST(d, n, c); d class c

#define DEFHCLASSTU(n, c) HTEMPLATE using H##c = Handle<c<n>>
#define HCLASSTU(n, c) template<typename T> class c; DEFHCLASSTU(n, c); template<typename T> class c

// Define HandleLink
// Cannot include Handle.h because it will cause a loop.
class HandleLink;
template<typename T>
class Handle;

HCLASS(Object)
{
public:
	HandleLink* link;
	
	Object ();
	virtual ~Object ();
};