#include "OpenGL.h"
#include <stdio.h>


bool SetupGL ()
{
	glewExperimental = true;
	
	if (glewInit () != GLEW_OK)
	{
		printf ("Failed to initialize GLEW\n");
		return false;
	}
	
	return true;
}

void ShutdownGL ()
{
	glfwTerminate();
}