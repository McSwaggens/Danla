//
// Created by daniel on 1/12/2018.
//

#include "Shapes.h"

#include "OpenGL.h"

HAttributeBuffer<Vector2> positionBuffer;
HAttributeBuffer<Matrix4> matrixBuffer;

HAttributeBuffer<Vector2> triangleVertices;
HAttributeBuffer<Vector2> triangleUV;

HAttributeBuffer<Vector2> quadVertices;
HAttributeBuffer<Vector2> quadUV;


HAttributeBatch Shapes::quad;
HAttributeBatch Shapes::triangle;

HAttributeBatch Shapes::positionedQuad;
HAttributeBatch Shapes::positionedTriangle;

HAttributeBatch Shapes::matrixQuad;

int drawCalls = 0;

void Shapes::Initialize ()
{
	triangleVertices = new AttributeBuffer<Vector2> (0, AttributeUsage::PerVertex, true,
		{
			   Vector2 (-1, -1),
			   Vector2 (1, -1),
			   Vector2 (0, 1)
		}
	);
	
	triangleUV = new AttributeBuffer<Vector2>(1, AttributeUsage::PerVertex, true,
		{
				Vector2(0.0f, 0.0f),
				Vector2(1.0f, 0.0f),
				Vector2(0.5f, 1.0f)
		}
	);
	
	quadVertices = new AttributeBuffer<Vector2>(0, AttributeUsage::PerVertex, true,
		{
			  Vector2 (-1, -1),
			  Vector2 (1, -1),
			  Vector2 (-1, 1),
			  Vector2 (1, -1),
			  Vector2 (1, 1),
			  Vector2 (-1, 1)
		}
	);
	
	quadUV = new AttributeBuffer<Vector2>(1, AttributeUsage::PerVertex, true,
		{
				Vector2 (0, 0),
				Vector2 (1, 0),
				Vector2 (0, 1),
				Vector2 (1, 0),
				Vector2 (1, 1),
				Vector2 (0, 1)
		}
	);
	
	
	positionBuffer = new AttributeBuffer<Vector2>(2, AttributeUsage::PerDraw, true);
	matrixBuffer = new AttributeBuffer<Matrix4>(2, AttributeUsage::PerDraw, true);
	
	quad = new AttributeBatch({ quadVertices, quadUV });
	triangle = new AttributeBatch({ triangleVertices, triangleUV });
	
	positionedQuad = new AttributeBatch({ quadVertices, quadUV, positionBuffer });
	positionedTriangle = new AttributeBatch({ triangleVertices, triangleUV, positionBuffer });
	
	matrixQuad = new AttributeBatch({ quadVertices, quadUV, matrixBuffer });
}

void DrawShape (HAttributeBatch& shape)
{
	bool usePositionBuffer = shape->buffers.size() > 2;
	
	shape->Enable();
	
	// Assuming vertices is element 0
	HAttributeBuffer<Vector2> vertexBuffer = shape->buffers[0];
	
	int drawCount = 1;
	
	if (usePositionBuffer)
	{
		drawCount = shape->buffers[2]->elements;
	}
	
	glDrawArraysInstanced(GL_TRIANGLES, 0, vertexBuffer->elements, drawCount);
	
	drawCalls++;
}
