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
#include "Camera.h"

//#include <windows.h>

//#include <signal.h>

#include <iostream>

void MainGameLoop ();

HWindow window;

MATERIALO (GaussianBlur, PostProcessorMaterial)
END_MATERIAL;

MATERIALO (VisualDepth, PostProcessorMaterial)
END_MATERIAL;

MATERIALO (SSAO, PostProcessorMaterial)
	TEXTURE(u_BlurredDepth, 2);
END_MATERIAL;

HGaussianBlur gaussianBlurHorizontal;
HGaussianBlur gaussianBlurVertical;
HUnitMaterial unitMaterial;
HVisualDepth visualDepth;
HSSAO ssao;

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

//BOOL WINAPI consoleHandler(DWORD signal)
//{
//	running = false;
//	return TRUE;
//}

void StartDanla ()
{
	setbuf(stdout, NULL);
	
//	if (!SetConsoleCtrlHandler(consoleHandler, TRUE))
//	{
//		printf("ERROR: Could not set control handler\n");
//	}
	
//	HANDLE currentProcess = GetCurrentProcess();
//	SetProcessAffinityMask(currentProcess, 1UL << 3);
	
	
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
	
	HShader depthShader = CreateShader("Depth");
	visualDepth = new VisualDepth(depthShader);
	
	HShader ssaoShader = CreateShader("AmbientOcclusion");
	ssao = new SSAO(ssaoShader);
	
	UseWindowForInput(window);
	
	world = new World();
	
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
	HFrameBuffer renderBuffer = new FrameBuffer (true, true, true, true);
	renderBuffer->colorBuffer->SetInterpolationNearest();
	
	HFrameBuffer gaussianBufferQuarterHDA = new FrameBuffer (true, false, IVector2(1920 / 4, 1080 / 4));
	HFrameBuffer gaussianBufferQuarterHDB = new FrameBuffer (true, false, IVector2(1920 / 4, 1080 / 4));
	HFrameBuffer gaussianBufferEighthHDA = new FrameBuffer (true, false, IVector2(1920 / 8, 1080 / 8));
	HFrameBuffer gaussianBufferEighthHDB = new FrameBuffer (true, false, IVector2(1920 / 8, 1080 / 8));
	
	HFrameBuffer alphaBuffer = new FrameBuffer (true, true, true, true);
	HFrameBuffer betaBuffer = new FrameBuffer (true, true, true, true);
	HFrameBuffer charlieBuffer = new FrameBuffer (true, true, true, true);
	alphaBuffer->colorBuffer->SetInterpolationNearest();
	betaBuffer->colorBuffer->SetInterpolationNearest();
	charlieBuffer->colorBuffer->SetInterpolationNearest();
	
	
	HPostProcessingStack ppStack = new PostProcessingStack(alphaBuffer, betaBuffer);
	ppStack->effects = {  };
	
	int numberOfTriangles = 1;
	
	HCamera camera = new Camera (0);
	world->camera = camera;
	camera->PreComputeMatrix();
	
	HTestActor testActor = Spawn(world, new TestActor(Vector2(0, 0)));
	//HTestActor testActor2 = Spawn(world, new TestActor(Vector2(1, 1)));
	
	
	HTexture unitTexture = LoadTexture("../Textures/ColorTest.png");
	unitMaterial->u_Texture = unitTexture;
	
	float cpuFPS = 0;
	float totalFPS = 0;
	
	float cpuFPSSum = 0;
	float totalFPSSum = 0;
	
	while (running)
	{
		float startTime = GetTime();
		
		PollTimeFull();
		
		window->PollEvents ();
		
		TickInputSystem();
		
		if (IsKeyDown(Keys::LeftAlt) && IsKeyPressed(Keys::Enter))
		{
			WindowMode windowMode = window->GetWindowMode();
			if (windowMode == WindowMode::FullScreen)
			{
				window->SetWindowMode(WindowMode::FullScreenWindowed, 0);
			}
			else if (windowMode == WindowMode::FullScreenWindowed)
			{
				window->SetWindowMode(WindowMode::FullScreen, 0);
			}
		}
		if (time >= 0.15f)
		{
			//ONCE(window->SetWindowMode(WindowMode::FullScreen, 1))
		}
		
		if (!running)
		{
			break;
		}
		
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
		
		camera->zoom += Reverse(GetScroll());
		
		Vector2 movementVector;
		movementVector.x -= IsKeyDown(Keys::A);
		movementVector.x += IsKeyDown(Keys::D);
		movementVector.y -= IsKeyDown(Keys::S);
		movementVector.y += IsKeyDown(Keys::W);
		
		//movementVector.x *= sin(time) / (PIx2);
		//movementVector.y *= cos(time) / (PIx2);
		
		camera->position += movementVector * camera->zoom * frameDelta;
		
		
		if (IsMouseKeyDown(MouseKeys::Left))
		{
			Spawn(world, new TestActor());
		}
		
		
		static float lastTime = 0;
		static int ticksThisSecond = 0;
		
		static float lastTickTime = 0.0f;
		
		if (time - lastTickTime > (1.0f/((float)tickRate)))
		{
			logicDelta = time - lastTickTime;
			lastTickTime = time;
			world->ComputeActors();
		}
		
		ticksThisSecond++;
		
		
		// Cool gradient
		// 89 89 222
		// 140 184 255
		
		renderBuffer->BindDraw();
		
		renderBuffer->Clear(Color(1.0, 1.0, 1.0));
		
		float aspect = 16.0f / 9.0f;
		Vector2 resolution = window->GetSize();
		Vector2 pixelation = Vector2(32 * aspect, 32);
		pixelation = Mix(pixelation, resolution, camera->zoom / 100.0f);
		
		IVector2 ipixelation = IVector2((int)pixelation.x, (int)pixelation.y);
		
		
		if (time - lastTime >= 1.0f)
		{
			std::stringstream newTitle;
			newTitle << "Danla, ";
			newTitle << "TestActors: ";
			newTitle << TestActor::count;
			newTitle << ", Rendered: " << TestActor::rendered;
			newTitle << ", FPS: ";
			newTitle << totalFPS;
			newTitle << ", CPU: " << cpuFPS << "ms";
			newTitle << ", Render Resolution: ";
			newTitle << "Width: " << ipixelation.x << " Height: " << ipixelation.y;
			newTitle << ", 50 / Zoom: " << (camera->zoom / 100.0f);
			window->SetTitle(newTitle.str());
			
			ticksThisSecond = 0;
			lastTime = time;
		}
		
		TestActor::rendered = 0;
		
		renderBuffer->Viewport(ipixelation);
		
		world->Render();
		world->DispatchRenderGroups();
		
		FrameBuffer::Copy(renderBuffer, ipixelation, charlieBuffer, false, true);
		FrameBuffer::Copy(charlieBuffer, renderBuffer, false, true);
		

		PostProcess(renderBuffer, gaussianBufferQuarterHDA, visualDepth);

		PostProcess(gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, gaussianBlurVertical);
		PostProcess(gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, gaussianBlurHorizontal);

		FrameBuffer::Copy(gaussianBufferQuarterHDA, gaussianBufferEighthHDA, true);

		PostProcess(gaussianBufferEighthHDA, gaussianBufferEighthHDB, gaussianBlurHorizontal);
		PostProcess(gaussianBufferEighthHDB, gaussianBufferEighthHDA, gaussianBlurVertical);

		FrameBuffer::Copy(gaussianBufferEighthHDA, charlieBuffer, true);
		
		ssao->u_BlurredDepth = charlieBuffer->colorBuffer;
		ssao->u_DepthTexture = alphaBuffer->colorBuffer;
		PostProcess(renderBuffer, betaBuffer, ssao);
		
		if (IsKeyDown(Keys::B))
		{
			FrameBuffer::Copy(betaBuffer, gaussianBufferQuarterHDA, true);

			PostProcess(gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, gaussianBlurVertical);
			PostProcess(gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, gaussianBlurHorizontal);

			FrameBuffer::Copy(gaussianBufferQuarterHDA, gaussianBufferEighthHDA, true);

			PostProcess(gaussianBufferEighthHDA, gaussianBufferEighthHDB, gaussianBlurHorizontal);
			PostProcess(gaussianBufferEighthHDB, gaussianBufferEighthHDA, gaussianBlurVertical);
		}
		
		//FrameBuffer::Copy(renderBuffer, defaultFrameBuffer, false);
		
		FrameBuffer::Copy(IsKeyDown(Keys::B) ? gaussianBufferEighthHDA : betaBuffer, defaultFrameBuffer, true);
		
		float endTime = GetTime ();
		
		cpuFPS = (endTime - startTime) * 1000;
		
		window->SwapBuffers ();
		
		endTime = GetTime ();
		totalFPS = 1.0f / (endTime - startTime);
		
		totalFPSSum += totalFPS;
		cpuFPSSum += cpuFPS;
		
	}
}