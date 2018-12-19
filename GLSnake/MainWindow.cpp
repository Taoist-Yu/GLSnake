#include "MainWindow.h"

#include<iostream>

#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "Scene.h"

MainWindow::MainWindow() 
{
	WindowInit(800, 600, "MainWindow");
}

MainWindow::MainWindow(GLuint width, GLuint height, std::string title)
{
	WindowInit(width, height, title);
}

MainWindow::~MainWindow()
{
}

void MainWindow::MainLoop()
{
	glEnable(GL_DEPTH_TEST);
	Shader shader("shader.vert", "shader.frag");
	Scene scene;
	GameObject human(&scene, "model/nanosuit/nanosuit.obj", shader);
	Camera camera(&scene,&human);

	human.transform.Translate(0, 0, 10);

	camera.transform.Translate(0,7,20);
	camera.Update();
	camera.Activate();

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.Update();

		glfwPollEvents();
	}
}

void MainWindow::WindowInit(GLuint width, GLuint height, std::string title)
{
	this->width = width;
	this->height = height;
	this->title = title;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);
}
