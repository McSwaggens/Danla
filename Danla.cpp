#include "Danla.h"

#include "OpenGL.h"
#include "Material.h"
#include "AttributeBatch.h"
#include "Time.h"
#include "FrameBuffer.h"
#include "PostProcessingStack.h"
#include "Shapes.h"
#include <math.h>
#include <iostream>

#define M_PI 3.14159265358979323846

void MainGameLoop ();

HWindow window;

MATERIAL (UnitMaterial)
END_MATERIAL;

MATERIAL (PPCopyMaterial)
	UNIFORM(Texture, u_InputTexture);
END_MATERIAL;

HPPCopyMaterial ppCopyMaterial;
HPPCopyMaterial ppCopyMaterial2;
HUnitMaterial unitMaterial;

bool running = false;

void StartDanla ()
{
	
	setbuf(stdout, NULL);
	
	printf ("Starting Danla...\n");
	
	//printf ("Sizeof Vector2 is %i bytes.\n", sizeof(Vector2));
	
	if (running)
	{
		return;
	}

	if (glfwInit () != GLFW_TRUE)
	{
		printf ("Failed to initialize GLFW\n");
		return;
	}

	window = new Window (1920, 1080, "Danla");
	
	glewExperimental = GL_TRUE;
	
	if (glewInit () != GLEW_OK)
	{
		glfwTerminate();
		printf ("Unable to setup GL\n");
		return;
	}

	PrintErrors ();
	
	Shapes::Initialize();
	
	defaultFrameBuffer = new FrameBuffer(0);
	
	HShader ppCopyShader = CreateShader ("PPCopy");
	ppCopyMaterial = new PPCopyMaterial (ppCopyShader);
	
	HShader ppCopyShader2 = CreateShader ("PPCopy2");
	ppCopyMaterial2 = new PPCopyMaterial (ppCopyShader2);
	
	HShader unitShader = CreateShader ("Unit");
	unitMaterial = new UnitMaterial(unitShader);

	//printf ("Window references = %i\n", window.link->references);

	running = true;

	MainGameLoop ();

	// Shutdown

	ShutdownGL ();
}

void ShutdownDanla ()
{
	running = false;
}

void PrintErrors ()
{
	GLenum error = glGetError ();
	if (error != GL_NO_ERROR)
	{
		printf ("ERROR! %i\n", error);
	}
}

String AlphaBool (bool b)
{
	return b ? "True" : "False";
}

void MainGameLoop ()
{
	
	
	
	HFrameBuffer alphaBuffer = new FrameBuffer (true, true, true);
	HFrameBuffer betaBuffer = new FrameBuffer (true, true, true);
	
	HPostProcessingStack ppStack = new PostProcessingStack(alphaBuffer, betaBuffer);
	
	
	while (running)
	{
		double startTime = GetTimeRaw();
		
		PollTimeFull();
		
		window->PollEvents ();
		
		static float foo = 0.0f;
		
		foo += 10 * delta;
		
		positionBuffer->Upload
		(
				{
						Vector2(0, 0),
				}
		);
		
		
		alphaBuffer->BindDraw();
		
		glEnable (GL_DEPTH_TEST);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.15f, 0.05f, 0.15f, 1.0f);
		
		unitMaterial->Enable ();
		
		DrawShape(Shapes::positionedTriangle);
		
		
		
		alphaBuffer->BindRead();
		betaBuffer->BindDraw();
		
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ppCopyMaterial2->Enable();
		
		DrawShape(Shapes::quad);
		
		FrameBuffer::Copy(betaBuffer, defaultFrameBuffer);
		
		double endTime = GetTimeRaw();
		double frameTime = endTime - startTime;
		printf ("renderTime PRE_SWAP: %lfms\n", frameTime * 1000.0);
		
		window->SwapBuffers ();
		
//		endTime = GetTimeRaw();
//		frameTime = endTime - startTime;
//		printf ("renderTime POST_SWAP: %lfms\n", frameTime * 1000.0);
	}
}