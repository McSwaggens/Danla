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
	void SetPosition (int x, int y);
	void SetSize (int width, int height);
	void SetVSync (bool enabled);
	void SetVisible (bool shown);
	void SwapBuffers ();
	void PollEvents ();
	Vector2 GetSize ();
};