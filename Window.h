#pragma once

#include "Standard.h"
#include "Handle.h"

HCLASS(Window) : public Object
{
private:
	void* pWindow;
public:
	
	Window (int width, int height, String title);
	~Window ();
	
	void Enable ();
	void SetTitle (String title);
	void SetPosition (IVector2 position);
	void SetSize (IVector2 size);
	bool IsFocused ();
	void SetVSync (bool enabled);
	void SetVisible (bool shown);
	void SwapBuffers ();
	void PollEvents ();
	void* GetPWindow ();
	IVector2 GetSize ();
};