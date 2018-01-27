#pragma once

#include "Standard.h"
#include "Handle.h"

enum class WindowMode
{
	FullScreen,
	FullScreenWindowed,
	Windowed,
	WindowedBorderless
};

#define CURRENT_MONITOR -1

HCLASS(Window) : public Object
{
private:
	void* pWindow;
	bool focused = true;
	bool vsync = false;
	bool unfocusedFPSLock = false;
	IVector2 cachedSize;
	WindowMode windowMode;
	
	/// @brief Updates the cached window size.
	/// @return true if the size has changed.
	bool UpdateSize ();
	
public:
	Window (int width, int height, String title);
	~Window ();
	
	void Enable ();
	void SetTitle (String title);
	void SetWindowMode (WindowMode windowMode, int monitor = 0);
	void SetPosition (IVector2 position);
	void SetSize (IVector2 size);
	void SetVSync (bool enabled);
	void SetVisible (bool shown);
	void PollEvents ();
	
	WindowMode GetWindowMode () const;
	bool IsFocused () const;
	void SwapBuffers () const;
	void* GetPWindow () const;
	IVector2 GetSize () const;
};