//
// Created by daniel on 1/17/2018.
//

#include "Input.h"
#include "OpenGL.h"

GLFWwindow* glfwWindow;

class InputCache
{
	bool pressMap[(sizeof(keyCodes)/4)-1] = { 0 };
public:
	
	inline bool& operator [] (std::size_t index)
	{
		return pressMap[index];
	}
};

InputCache currentKeyboardMap;
InputCache previousKeyboardMap;

void TickInputSystem ()
{
	previousKeyboardMap = currentKeyboardMap;
	currentKeyboardMap = InputCache();
	
	for (int i = 0; i < (int)Keys::Menu; i++)
	{
		int keyCode = keyCodes[i];
		
		bool pressed = glfwGetKey(glfwWindow, keyCode) == GLFW_PRESS;
		
		currentKeyboardMap[i] = pressed;
	}
}

void UseWindowForInput (HWindow window)
{
	glfwWindow = (GLFWwindow*)window->GetPWindow();
}

bool IsKeyDown (Keys key)
{
	return currentKeyboardMap[(int)key];
}

bool IsKeyUp (Keys key)
{
	return !currentKeyboardMap[(int)key];
}

bool IsKeyPressed (Keys key)
{
	return currentKeyboardMap[(int)key] && !previousKeyboardMap[(int)key];
}

bool IsKeyReleased (Keys key)
{
	return !currentKeyboardMap[(int)key] && previousKeyboardMap[(int)key];
}
