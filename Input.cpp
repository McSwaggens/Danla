//
// Created by daniel on 1/17/2018.
//

#include "Input.h"
#include "OpenGL.h"

GLFWwindow* glfwWindow;

class InputCache
{
public:
	bool keyboard[(sizeof(keyCodes)/4)-1] = { 0 };
	bool mouse[(sizeof(mouseKeyCodes)/4)-1] = { 0 };
};

InputCache currentInputCache;
InputCache previousInputCache;

double glfwMouseScrollCurrentX = 0.0f;
double glfwMouseScrollCurrentY = 0.0f;

float scroll = 0.0f;

void TickInputSystem ()
{
	previousInputCache = currentInputCache;
	currentInputCache = InputCache();
	
	for (int i = 0; i < (int)Keys::Menu; i++)
	{
		int keyCode = keyCodes[i];
		
		bool pressed = glfwGetKey(glfwWindow, keyCode) == GLFW_PRESS;
		
		currentInputCache.keyboard[i] = pressed;
	}
	
	for (int i = 0; i < (int)MouseKeys::Middle; i++)
	{
		int keyCode = mouseKeyCodes[i];
		
		bool pressed = glfwGetMouseButton(glfwWindow, keyCode) == GLFW_PRESS;
		
		currentInputCache.mouse[i] = pressed;
	}
	
	scroll = (float)glfwMouseScrollCurrentY;
	
	glfwMouseScrollCurrentY = 0.0f;
	glfwMouseScrollCurrentX = 0.0f;
}

void UseWindowForInput (HWindow window)
{
	glfwWindow = (GLFWwindow*)window->GetPWindow();
}

bool IsKeyDown (Keys key)
{
	return currentInputCache.keyboard[(int)key];
}

bool IsKeyUp (Keys key)
{
	return !currentInputCache.keyboard[(int)key];
}

bool IsKeyPressed (Keys key)
{
	return currentInputCache.keyboard[(int)key] && !previousInputCache.keyboard[(int)key];
}

bool IsKeyReleased (Keys key)
{
	return !currentInputCache.keyboard[(int)key] && previousInputCache.keyboard[(int)key];
}

float GetScroll ()
{
	return scroll;
}

bool IsMouseKeyDown (MouseKeys mouseKey)
{
	return currentInputCache.mouse[(int)mouseKey];
}

bool IsMouseKeyUp (MouseKeys mouseKey)
{
	return !currentInputCache.mouse[(int)mouseKey];
}

bool IsMouseKeyPressed (MouseKeys mouseKey)
{
	return currentInputCache.mouse[(int)mouseKey] && !previousInputCache.mouse[(int)mouseKey];
}

bool IsMouseKeyReleased (MouseKeys mouseKey)
{
	return !currentInputCache.mouse[(int)mouseKey] && previousInputCache.mouse[(int)mouseKey];
}
