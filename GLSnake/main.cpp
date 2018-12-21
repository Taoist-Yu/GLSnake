#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include "GLMainWindow.h"
#include "MainWindow.h"
#include "Shader.h"
#include "Mesh.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	GLMainWindow window(hInstance, nCmdShow);
	window.MainLoop();
	return 0;
}