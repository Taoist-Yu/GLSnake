#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include "MainWindow.h"
#include "Shader.h"
#include "Mesh.h"

int main()
{
	MainWindow window;
	window.MainLoop();
	return 0;
}