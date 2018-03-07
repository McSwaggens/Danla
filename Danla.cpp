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
#include "Laser.h"
#include "UFloat.h"

#include <windows.h>

//#include <signal.h>

#include <iostream>

void MainGameLoop ();

HWindow window;

MATERIALO (GaussianBlur, PostProcessorMaterial)
END_MATERIAL;

MATERIALO (BloomBlur, PostProcessorMaterial)
	UNIFORM(UFloat, u_Split);
END_MATERIAL;

MATERIALO (VisualDepth, PostProcessorMaterial)
END_MATERIAL;

MATERIALO (Plain, PostProcessorMaterial)
	TEXTURE(u_BloomTexture, 2);
END_MATERIAL;

MATERIALO (HDRExtractor, PostProcessorMaterial)
END_MATERIAL;

MATERIALO (SSAO, PostProcessorMaterial)
	TEXTURE(u_BlurredDepth, 2);
END_MATERIAL;

HGaussianBlur gaussianBlurHorizontal;
HGaussianBlur gaussianBlurVertical;
HBloomBlur bloomBlurHorizontal;
HBloomBlur bloomBlurVertical;
HUnitMaterial unitMaterial;
HVisualDepth visualDepth;
HSSAO ssao;
HHDRExtractor hdrExtractor;
HPlain plain;

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
	
	HANDLE currentProcess = GetCurrentProcess();
	SetProcessAffinityMask(currentProcess, 1UL << 3);
	
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
	
	HShader bloomBlurHorizontalShader = CreateShader ("BloomBlurHorizontal");
	bloomBlurHorizontal = new BloomBlur (bloomBlurHorizontalShader);
	
	HShader bloomBlurVerticalShader = CreateShader ("BloomBlurVertical");
	bloomBlurVertical = new BloomBlur (bloomBlurVerticalShader);
	
	HShader unitShader = CreateShader ("Unit");
	unitMaterial = new UnitMaterial(unitShader);
	
	HShader laserShader = CreateShader ("Laser");
	laserMaterial = new LaserMaterial(laserShader);
	
	HShader hdrExtractorShader = CreateShader ("HDRExtractor");
	hdrExtractor = new HDRExtractor(hdrExtractorShader);
	
	HShader depthShader = CreateShader("Depth");
	visualDepth = new VisualDepth(depthShader);
	
	HShader plainShader = CreateShader("Plain");
	plain = new Plain (plainShader);
	
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
	renderBuffer->hdrBuffer->SetInterpolationNearest();
	
	
	HFrameBuffer gaussianBufferQuarterHDA = new FrameBuffer (true, false, IVector2(1920 / 4, 1080 / 4));
	HFrameBuffer gaussianBufferQuarterHDB = new FrameBuffer (true, false, IVector2(1920 / 4, 1080 / 4));
	HFrameBuffer gaussianBufferEighthHDA = new FrameBuffer (true, false, IVector2(1920 / 8, 1080 / 8));
	HFrameBuffer gaussianBufferEighthHDB = new FrameBuffer (true, false, IVector2(1920 / 8, 1080 / 8));
	
//	HFrameBuffer alphaBuffer = new FrameBuffer (true, false, true, false);
//	HFrameBuffer betaBuffer = new FrameBuffer (true, true, true, false);
//	HFrameBuffer charlieBuffer = new FrameBuffer (true, true, true, false);
//	alphaBuffer->colorBuffer->SetInterpolationNearest();
//	betaBuffer->colorBuffer->SetInterpolationNearest();
//	charlieBuffer->colorBuffer->SetInterpolationNearest();
	
	
	HCamera camera = new Camera (0);
	world->camera = camera;
	camera->PreComputeMatrix();
	
	HTestActor testActor = Spawn(world, new TestActor(Vector2(0, 0)));
	
	HLaser laser = Spawn(world, new Laser(), Vector2(2, 2));
	
	HTexture unitTexture = LoadTexture("../Textures/ColorTest.png");
	HTexture unitBloomTexture = LoadTexture("../Textures/BloomTest.png");
	unitMaterial->u_BloomTexture = unitBloomTexture;
	unitMaterial->u_Texture = unitTexture;
	
	float cpuFPS = 0;
	float totalFPS = 0;
	
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
		
		
		camera->zoom += Reverse(GetScroll());
		
		Vector2 movementVector;
		movementVector.x -= IsKeyDown(Keys::A);
		movementVector.x += IsKeyDown(Keys::D);
		movementVector.y -= IsKeyDown(Keys::S);
		movementVector.y += IsKeyDown(Keys::W);
		
		
		camera->position += movementVector * camera->zoom * frameDelta;
		
		
		if (IsMouseKeyDown(MouseKeys::Left))
		{
			//Spawn(world, new TestActor());
		}
		
		
		
		static float lastTime = 0;
		static int ticksThisSecond = 0;
		static int framesThisSecond = 0;
		
		static float culmination = 0.0f;
		static const float logicFrequency = (1.0f/((float)60.0f));
		
		culmination += frameDelta;
		
		if (culmination >= logicFrequency)
		{
			logicDelta = culmination;
			culmination = culmination - logicFrequency;
			world->ComputeActors();
			ticksThisSecond++;
		}
		
		
		framesThisSecond++;
		
		float renderStartTime = GetTime();
		
		renderBuffer->BindDraw();
		
		renderBuffer->Clear(Color(1.0, 1.0, 1.0));
		
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		
		
		static float _lastTime = 0;
		static int _framesThisSecond = 0;
		static int _ticksThisSecond = 0;
		
		if (time - _lastTime >= 1.0f)
		{
			_framesThisSecond = framesThisSecond;
			_ticksThisSecond = ticksThisSecond;
			framesThisSecond = 0;
			ticksThisSecond = 0;
			_lastTime = time;
		}
		
		if (time - lastTime >= 1.0f)
		{
			std::stringstream newTitle;
			newTitle << "Danla, "
			<< "TestActors: "
			<< TestActor::count
			<< ", Rendered: " << TestActor::rendered
			<< ", FPS: " << totalFPS << ", (counted: " << _framesThisSecond << ")"
			<< ", CPU: " << cpuFPS << "ms"
			<< ", Ticks: " << _ticksThisSecond;
			window->SetTitle(newTitle.str());
			
			lastTime = time;
		}
		
		TestActor::rendered = 0;
		
		world->Render();
		world->DispatchRenderGroups();
		
		
		glDisable(GL_BLEND);
		
		FrameBuffer::Copy(renderBuffer, gaussianBufferQuarterHDA, false, false, 1);
		
//		PostProcess (gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, bloomBlurHorizontal);
//		PostProcess (gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, bloomBlurVertical);
		
		FrameBuffer::Copy(gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, false, false, 0);
		
		
//		PostProcess (gaussianBufferEighthHDA, gaussianBufferEighthHDB, bloomBlurHorizontal);
//		PostProcess (gaussianBufferEighthHDB, gaussianBufferEighthHDA, bloomBlurVertical);
		
		FrameBuffer::Copy(gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, false, false, 0);
		
		
//		PostProcess (gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, bloomBlurHorizontal);
//		PostProcess (gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, bloomBlurVertical);
		
		FrameBuffer::Copy(gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, false, false, 0);
		
		
//		PostProcess(renderBuffer, alphaBuffer, plain);
		
		
//		PostProcess(renderBuffer, gaussianBufferQuarterHDA, visualDepth);
//
//		PostProcess(gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, gaussianBlurVertical);
//		PostProcess(gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, gaussianBlurHorizontal);
//
//		FrameBuffer::Copy(gaussianBufferQuarterHDA, gaussianBufferEighthHDA, true);
//
//		PostProcess(gaussianBufferEighthHDA, gaussianBufferEighthHDB, gaussianBlurHorizontal);
//		PostProcess(gaussianBufferEighthHDB, gaussianBufferEighthHDA, gaussianBlurVertical);
//
//		FrameBuffer::Copy(gaussianBufferEighthHDA, charlieBuffer, true);
//
//		ssao->u_BlurredDepth = charlieBuffer->colorBuffer;
//		ssao->u_DepthTexture = alphaBuffer->colorBuffer;
//		PostProcess(renderBuffer, betaBuffer, ssao);
		

//		if (IsKeyDown(Keys::B))
//		{
//			FrameBuffer::Copy(betaBuffer, gaussianBufferQuarterHDA, true);
//
//			PostProcess(gaussianBufferQuarterHDA, gaussianBufferQuarterHDB, gaussianBlurVertical);
//			PostProcess(gaussianBufferQuarterHDB, gaussianBufferQuarterHDA, gaussianBlurHorizontal);
//
//			FrameBuffer::Copy(gaussianBufferQuarterHDA, gaussianBufferEighthHDA, true);
//
//			PostProcess(gaussianBufferEighthHDA, gaussianBufferEighthHDB, gaussianBlurHorizontal);
//			PostProcess(gaussianBufferEighthHDB, gaussianBufferEighthHDA, gaussianBlurVertical);
//		}
		
		
		PrintErrors();
		
//		FrameBuffer::CopyToDefaultFrameBuffer(alphaBuffer);
		
		float endTimeCPU = GetTime ();
		
		cpuFPS = (endTimeCPU - startTime) * 1000.0f;
		
		window->SwapBuffers ();
		
		float endTime = GetTime ();
		totalFPS = 1.0f / (endTime - renderStartTime);
	}
}