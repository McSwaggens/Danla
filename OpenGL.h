#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

// WARNING:
//	THIS FILE SHOULD ONLY BE INCLUDED INSIDE OF CPP FILES.

bool SetupGL ();
void ShutdownGL ();