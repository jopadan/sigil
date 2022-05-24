#include "GLFW/glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#ifdef __MINGW32__
	#include <windows.h>
#endif

static OSL_IMAGE *sliProgramWindow = NULL;
static OSL_CONTROLLER *sliKeys = NULL;
static int sliWindowWidth = 0;
static int sliWindowHeight = 0;

void sliOpenWindow(
	int width,
	int height,
	const char *title,
	int fullScreen,
	int *frameWidth,
	int *frameHeight
)
{
	// types enabling us to access WGL functionality for enabling vsync in Windows
	//#ifdef __MINGW32__
		//typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
		//PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
    //#endif

	// start up OSLib
	oslInit(0);
	oslInitGfx(OSL_PF_8888,1);
	oslSetFramerate(60);

	oslShowSplashScreen(1);
	// set our OpenGL 3.2 context to something that doesn't support any old-school shit

	// create our OpenGL window
	sliProgramWindow = oslGetDrawBuffer();

	frameWidth = sliProgramWindow->sizeX();
	frameHeight = sliProgramWindow->sizeY();

	sliWindowWidth = width;
	sliWindowHeight = height;
}

void sliShowCursor(int showCursor)
{
	glfwSetInputMode(sliProgramWindow, GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void sliCloseWindow()
{
	oslEndGfx();
	oslQuit();
	sliProgramWindow = NULL;
}

int sliIsWindowOpen()
{
	return sliProgramWindow != NULL;
}

int sliShouldClose()
{
	return osl_quit;
}

int sliGetKey(int key)
{
	return sliGetKeys()->pressed == key;
}

int sliGetMouseButton(int button)
{

	return sliGetKeys()-> == GLFW_PRESS;
}

void sliGetMousePos(int *posX, int *posY)
{
	*posX = sliGetInput()->mouse.analogX;
	*posY = sliWindowHeight - sliGetInput()->mouse.analogY;
}

double sliGetTime()
{
	return oslGetTime();
}

void sliPollAndSwap()
{
//	oslPollEvents();
	oslSwapBuffers();
}
