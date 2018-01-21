#include "Window.h"
#include "OpenGL.h"
#include "Danla.h"
#include <math.h>
#include <stdio.h>
#include "FrameBuffer.h"

#define gWindow (GLFWwindow*)pWindow

Window::Window (int width, int height, String title)
{
	int monitorCount = 0;
	GLFWmonitor* monitor = glfwGetMonitors(&monitorCount)[1];
	
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
	
	width = videoMode->width;
	height = videoMode->height;
	
	glfwWindowHint(GLFW_DECORATED, 1);
	glfwWindowHint(GLFW_SAMPLES, 0);
	
	GLFWwindow* windowPointer = glfwCreateWindow (width, height, title.c_str(), 0, NULL);
	
	int monPosX, monPosY;
	
	glfwGetMonitorPos(monitor, &monPosX, &monPosY);
	
	glfwSetWindowPos(windowPointer, monPosX, monPosY);
	
	pWindow = (void*)windowPointer;
	Enable();
	
	SetVSync(false);
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
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}
}

IVector2 Window::GetSize ()
{
	int width, height;
	glfwGetWindowSize(gWindow, &width, &height);
	return IVector2(width, height);
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

void Window::SwapBuffers ()
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
	IVector2 resolutionCopy = GetSize();
	
	glfwPollEvents ();
	
	IVector2 resolution = GetSize ();
	
	if ((resolution.x != 0 && resolution.y != 0) && (resolution.x != resolutionCopy.x || resolution.y != resolutionCopy.y))
	{
		for (auto frameBuffer : frameBuffers)
		{
			frameBuffer->OnWindowSizeChanged(this);
		}
	}
	
	glViewport(0, 0, resolution.x, resolution.y);
	
	if (glfwWindowShouldClose(gWindow) || glfwGetKey(gWindow, GLFW_KEY_ESCAPE) || (glfwGetKey(gWindow, GLFW_KEY_LEFT_ALT) && glfwGetKey(gWindow, GLFW_KEY_F4)))
	{
		ShutdownDanla ();
	}
}

void* Window::GetPWindow ()
{
	return pWindow;
}

bool Window::IsFocused ()
{
}
