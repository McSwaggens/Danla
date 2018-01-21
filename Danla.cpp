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
#include <fstream>
#include <sstream>

#include "PostProcessing.h"
#include "Keys.h"
#include "Input.h"
#include "TestActor.h"

#include <windows.h>

void MainGameLoop ();

HWindow window;

MATERIALO (GaussianBlur, PostProcessorMaterial)
END_MATERIAL;

HGaussianBlur gaussianBlurHorizontal;
HGaussianBlur gaussianBlurVertical;
HUnitMaterial unitMaterial;

HWorld world;

bool running = false;

bool InitializeStandardShader ()
{
	std::ifstream ifstream("../Shaders/Standard.glsl");
	if (ifstream.good())
	{
		std::stringstream buffer;
		buffer << ifstream.rdbuf();
		String str = buffer.str();
		standardShaderLibraryString = str;
		printf ("Standard shader library loaded.\n");
		return true;
	}
	else
	{
		printf ("Could not find Standard shader library file...\n");
		return false;
	}
}

void StartDanla ()
{
	setbuf(stdout, NULL);
	
	HANDLE currentThread = GetCurrentProcess();
	SetProcessAffinityMask(currentThread, 1UL << 3);
	
	printf ("Starting Danla...\n");
	
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
	
	InitializeStandardShader ();
	
	defaultFrameBuffer = new FrameBuffer(0);
	
	HShader gaussianShaderHorizontal = CreateShader ("GaussianBlurHorizontal");
	gaussianBlurHorizontal = new GaussianBlur (gaussianShaderHorizontal);
	
	HShader gaussianShaderVertical = CreateShader ("GaussianBlurVertical");
	gaussianBlurVertical = new GaussianBlur (gaussianShaderVertical);
	
	HShader unitShader = CreateShader ("Unit");
	unitMaterial = new UnitMaterial(unitShader);
	
	UseWindowForInput(window);
	
	world = new World();
	
	//printf ("Window references = %i\n", window.link->references);
	
	running = true;
	
	MainGameLoop ();
	
	window->SetVSync(true);
	
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
	
	HFrameBuffer gaussianBufferQuarterHDA = new FrameBuffer (true, false, IVector2(1920 / 4, 1080 / 4));
	HFrameBuffer gaussianBufferQuarterHDB = new FrameBuffer (true, false, IVector2(1920 / 4, 1080 / 4));
	HFrameBuffer gaussianBufferEighthHDA = new FrameBuffer (true, false, IVector2(1920 / 8, 1080 / 8));
	HFrameBuffer gaussianBufferEighthHDB = new FrameBuffer (true, false, IVector2(1920 / 8, 1080 / 8));
	
	HFrameBuffer alphaBuffer = new FrameBuffer (true, true, true, true);
	HFrameBuffer betaBuffer = new FrameBuffer (true, true, true, true);
	
	HFrameBuffer renderBuffer = new FrameBuffer (true, true, true, true);
	
	HPostProcessingStack ppStack = new PostProcessingStack(alphaBuffer, betaBuffer);
	ppStack->effects = {  };
	
	int numberOfTriangles = 1;
	
	
	HTestActor testActor = Spawn(world, new TestActor());
	testActor.GhostDereference();
	
	HTestActor testActor2 = Spawn(world, new TestActor());
	testActor2.GhostDereference();
	
	
	while (running)
	{
		PollTimeFull();
		
		window->PollEvents ();
		
		
		if (IsKeyDown(Keys::Up))
		{
			numberOfTriangles++;
		}
		
		if (IsKeyDown(Keys::Down))
		{
			if (numberOfTriangles != 0)
			{
				numberOfTriangles--;
			}
		}
		
		TickInputSystem();
		
		static float lastTime = 0;
		static int ticksThisSecond = 0;
		
		ticksThisSecond++;
		
		if (time - lastTime >= 1)
		{
			
			std::stringstream newTitle;
			newTitle << "Danla, ";
			newTitle << "Triangles: ";
			newTitle << TestActor::count;
			newTitle << ", FPS: ";
			newTitle << ticksThisSecond;
			window->SetTitle(newTitle.str());
			
			//printf ("%s\n", newTitle.str().c_str());
			
			ticksThisSecond = 0;
			lastTime = time;
		}
		
		// Cool gradient
		// 89 89 222
		// 140 184 255
		
		renderBuffer->BindDraw();
		
		renderBuffer->Clear(Color(0.15f, 0.05f, 0.15f));
		
		unitMaterial->Enable ();
		
		world->ComputeActors();
		world->Render();
		world->DispatchRenderGroups();
		
		if (IsKeyDown(Keys::B))
		{
			FrameBuffer::Copy(renderBuffer, gaussianBufferQuarterHDA, false);
			
			PostProcess(gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, gaussianBlurVertical);
			PostProcess(gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, gaussianBlurHorizontal);
			
			FrameBuffer::Copy(gaussianBufferQuarterHDA, gaussianBufferEighthHDA, false);
			
			PostProcess(gaussianBufferEighthHDA, gaussianBufferEighthHDB, gaussianBlurHorizontal);
			PostProcess(gaussianBufferEighthHDB, gaussianBufferEighthHDA, gaussianBlurVertical);
		}
		
		FrameBuffer::Copy(IsKeyDown(Keys::B) ? gaussianBufferEighthHDA : renderBuffer, defaultFrameBuffer, true);
		
		
		window->SwapBuffers ();
	}
}