//
// Created by daniel on 1/22/2018.
//

#include "Camera.h"

#include "OpenGL.h"
#include "Time.h"
#include "Math.h"

HCamera activeCamera;

Camera::Camera ()
{
}

Camera::Camera (Vector3 position)
{
}

void Camera::PreComputeMatrix ()
{
	zoom = Clamp(zoom, 1.0f, 100.0f);
	
	
	glm::mat4 proj = glm::ortho(-zoom, zoom, -zoom * aspectYScale, zoom * aspectYScale, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1);
	view = glm::translate(view, glm::vec3(Reverse(position.x), Reverse(position.y), 0));
	
	glm::mat4 rpv = proj * view;
	
	Matrix4& dmat = (Matrix4&)(rpv);
	pvMatrix = dmat;
}

void Camera::RenderWorld (HWorld world)
{
	activeCamera = this;
	
	//world->DispatchRenderGroups();
}
