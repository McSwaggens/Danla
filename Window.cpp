#include "Window.h"
#include "OpenGL.h"
#include "Danla.h"
#include <math.h>
#include <stdio.h>


#define gWindow (GLFWwindow*)pWindow

Window::Window (int width, int height, String title)
{
	int monitorCount = 0;
	GLFWmonitor* monitor = glfwGetMonitors(&monitorCount)[1];
	
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
	
	width = videoMode->width;
	height = videoMode->height;
	
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

void Window::SetPosition (int x, int y)
{
	glfwSetWindowPos(gWindow, x, y);
}

void Window::SetSize (int width, int height)
{
	glfwSetWindowSize(gWindow, width, height);
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

Vector2 Window::GetSize ()
{
	int width, height;
	glfwGetWindowSize(gWindow, &width, &height);
	return Vector2(width, height);
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
//  // Has really annoying stuttering
//	// You shouldn't use this code.
//	float _time;
//	do
//	{
//		_time = GetTime();
//	} while (_time - lastSwapTime < targetFrameTime);
//
//
//	lastSwapTime = _time;
	glfwSwapBuffers (gWindow);
}

void Window::PollEvents ()
{
	glfwPollEvents ();
	
	Vector2 resolution = GetSize ();
	
	glViewport(0, 0, resolution.x, resolution.y);
	
	if (glfwWindowShouldClose(gWindow) || glfwGetKey(gWindow, GLFW_KEY_ESCAPE) || (glfwGetKey(gWindow, GLFW_KEY_LEFT_ALT) && glfwGetKey(gWindow, GLFW_KEY_F4)))
	{
		ShutdownDanla ();
	}
}