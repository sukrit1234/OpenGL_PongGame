// TestOpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include "BounceBallApp.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UBounceBallApp App;
	App.Start("level1");
	return 0;
}