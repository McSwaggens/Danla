#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

// WARNING:
//	THIS FILE SHOULD ONLY BE INCLUDED INSIDE OF CPP FILES.

bool SetupGL ();
void ShutdownGL ();

#include "Vector2.h"
#include "Vector3.h"

inline glm::vec3& Convert (Vector3& vector3)
{
	return (glm::vec3&)(vector3);
}