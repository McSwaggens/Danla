#include "Window.h"
#include "OpenGL.h"
#include "Danla.h"
#include <stdio.h>
#include "FrameBuffer.h"

#define gWindow (GLFWwindow*)pWindow

IVector2 _cachedWindowSize;

extern double glfwMouseScrollCurrentX;
extern double glfwMouseScrollCurrentY;

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	_cachedWindowSize = IVector2(width, height);
	//printf ("Width: %i, Height: %i\n", width, height);
}

void WindowScrollCallback(GLFWwindow* window, double x, double y)
{
	glfwMouseScrollCurrentX = x;
	glfwMouseScrollCurrentY = y;
}

Window::Window (int width, int height, String title)
{
	int monitorCount = 0;
	GLFWmonitor* monitor = glfwGetMonitors(&monitorCount)[1];
	
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
	
	width = videoMode->width;
	height = videoMode->height;
	
	glfwWindowHint(GLFW_DECORATED, 1);
	//glfwWindowHint(GLFW_MAXIMIZED, 1);
	//glfwWindowHint(GLFW_CURSOR_HIDDEN, 1);
	glfwWindowHint(GLFW_SAMPLES, 0);
	
	GLFWwindow* windowPointer = glfwCreateWindow (width, height, title.c_str(), 0, NULL);
	
	//glfwSetInputMode(windowPointer, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	_cachedWindowSize = IVector2(width, height);
	
	windowMode = WindowMode::FullScreen;
	
	int monPosX, monPosY;
	
	glfwGetMonitorPos(monitor, &monPosX, &monPosY);
	
	glfwSetWindowPos(windowPointer, monPosX, monPosY);
	glfwSetFramebufferSizeCallback(windowPointer, WindowSizeCallback);
	glfwSetScrollCallback(windowPointer, WindowScrollCallback);
	glfwMaximizeWindow(windowPointer);
	
	pWindow = (void*)windowPointer;
	Enable();
	
	SetVSync(false);
	
	
	UpdateSize();
}

Window::~Window ()
{
	glfwDestroyWindow (gWindow);
}

void Window::Enable ()
{
	glfwMakeContextCurrent (gWindow);
	glfwFocusWindow(gWindow); // Removing this random glfw command will crash the engine... Don't ask why, the computer gods have deemed me not worthy of working code.
}

void Window::SetPosition (IVector2 position)
{
	glfwSetWindowPos(gWindow, position.x, position.y);
}

void Window::SetSize (IVector2 size)
{
	glfwSetWindowSize(gWindow, size.x, size.y);
}

void Window::SetTitle (String title)
{
	glfwSetWindowTitle(gWindow, title.c_str());
}

void Window::SetVSync (bool enabled)
{
	vsync = enabled;
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}
}

IVector2 Window::GetSize () const
{
	return cachedSize;
}

void Window::SetVisible (bool shown)
{
	if (shown)
	{
		glfwShowWindow (gWindow);
	}
	else
	{
		glfwHideWindow (gWindow);
	}
}

float targetFrameTime = 1.0f / 60.0f;
float lastSwapTime = 0.0f;

void Window::SwapBuffers () const
{
	
//	// Has really annoying stuttering
//	// You shouldn't use this code.
//	float _time;
//	do
//	{
//		_time = GetTime();
//	} while (_time - lastSwapTime < targetFrameTime);
//	lastSwapTime = _time;
	
	glfwSwapBuffers (gWindow);
}

void Window::PollEvents ()
{
	glfwPollEvents ();
	
	bool resolutionChanged = UpdateSize();
	
	IVector2 resolution = GetSize ();
	
	if (resolutionChanged && (resolution.x != 0 && resolution.y != 0))
	{
		for (auto frameBuffer : frameBuffers)
		{
			frameBuffer->OnWindowSizeChanged(this);
		}
	}
	
	if (focused != (focused = (bool)glfwGetWindowAttrib(gWindow, GLFW_FOCUSED)))
	{
		
		
		if (unfocusedFPSLock)
		{
			if (focused)
			{
				glfwSwapInterval((int)vsync);
			}
			else
			{
				glfwSwapInterval(2);
			}
		}
	}
	
	
	glViewport(0, 0, resolution.x, resolution.y);
	
	if (glfwWindowShouldClose(gWindow) || glfwGetKey(gWindow, GLFW_KEY_ESCAPE) || (glfwGetKey(gWindow, GLFW_KEY_LEFT_ALT) && glfwGetKey(gWindow, GLFW_KEY_F4)))
	{
		ShutdownDanla ();
	}
}

void* Window::GetPWindow () const
{
	return pWindow;
}

bool Window::IsFocused () const
{
	return focused;
}

void Window::SetWindowMode (WindowMode _windowMode, int monitorID)
{
	int monitorCount = 0;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	
	
	GLFWmonitor* currentMonitor = glfwGetWindowMonitor(gWindow);
	
	bool hasCurrentMonitor = currentMonitor != 0;
	const GLFWvidmode* currentVideoMode;
	
	if (hasCurrentMonitor)
	{
		currentVideoMode = glfwGetVideoMode(currentMonitor);
	}
	
	
	if (monitorID >= monitorCount)
	{
		printf ("Cannot find monitor %i\n", monitorID);
		return;
	}
	
	GLFWmonitor* selectedMonitor;
	const GLFWvidmode* selectedVideoMode;
	
	if (monitorID == CURRENT_MONITOR && !hasCurrentMonitor)
	{
		monitorID = 0;
	}
	
	if (monitorID == CURRENT_MONITOR)
	{
		selectedVideoMode = currentVideoMode;
		selectedMonitor = currentMonitor;
	}
	else
	{
		selectedMonitor = monitors[monitorID];
		selectedVideoMode = glfwGetVideoMode(selectedMonitor);
	}
	
	IVector2 selectedMonitorPosition;
	glfwGetMonitorPos(selectedMonitor, &selectedMonitorPosition.x, &selectedMonitorPosition.y);
	
	if (_windowMode == WindowMode::FullScreen)
	{
		glfwSetWindowMonitor(gWindow, selectedMonitor, 0, 0, selectedVideoMode->width, selectedVideoMode->height, selectedVideoMode->refreshRate);
		windowMode = WindowMode::FullScreen;
	}
	else if (_windowMode == WindowMode::FullScreenWindowed)
	{
		glfwSetWindowMonitor(gWindow, 0, selectedMonitorPosition.x, selectedMonitorPosition.y, selectedVideoMode->width, selectedVideoMode->height, selectedVideoMode->refreshRate);
		windowMode = WindowMode::FullScreenWindowed;
	}
	SetVSync(vsync);
	
}

bool Window::UpdateSize ()
{
	IVector2 oldSize = cachedSize;
	
	cachedSize = _cachedWindowSize;
	
	return oldSize.x != cachedSize.x || oldSize.y != cachedSize.y;
}

WindowMode Window::GetWindowMode () const
{
	return windowMode;
}
