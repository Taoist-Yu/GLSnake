#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include "MainWindow.h"
#include "Shader.h"
#include "Mesh.h"

int main()
{
	
	MainWindow::CreateInstance(1024, 768, "Snake");
	MainWindow::Instance()->MainLoop();
	return 0;
}