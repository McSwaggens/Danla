//
// Created by daniel on 1/20/2018.
//

#include "Transform.h"
#include "OpenGL.h"

Transform::Transform (const Vector3& position, const Vector2& scale, float rotation) : position(position), scale(scale),
																					   rotation(rotation)
{
//	glm::mat4& matrix = matrix;
//	matrix = glm::mat4(1);
}

Transform::Transform ()
{
	position = 0;
	scale = 1;
	rotation = 0;
}

Matrix4& Transform::GetMatrix ()
{
	glm::mat4& matrix = (glm::mat4&)modelMatrix;
	
	matrix = glm::mat4(1);
	matrix = glm::translate(matrix, (glm::vec3&)position);
	matrix = glm::rotate(matrix, rotation, glm::vec3(0, 0, 1));
	
	return modelMatrix;
}

void Transform::SetPosition (Vector2 v)
{
}

void Transform::Move (Vector2 v)
{

}

void Transform::SetScale (Vector2 v)
{

}

void Transform::SetRotation (float f)
{

}
