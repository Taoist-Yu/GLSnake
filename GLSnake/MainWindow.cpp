#include "MainWindow.h"

#include<iostream>

#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "Input.h"
#include "Ball.h"
#include "Confine.h"
#include "Snake.h"

void MainWindow::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MainWindow::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		Input::KeyDownSet.insert(key);
	}
	if (action == GLFW_REPEAT) {
		Input::KeyRepeatSet.insert(key);
	}
	if (action == GLFW_RELEASE) {
		Input::KeyUpSet.insert(key);
	}
}

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
	glfwTerminate();
}

void MainWindow::MainLoop()
{
	glEnable(GL_DEPTH_TEST);
	
	Scene level1;
	//Level1
	Confine confine(&level1);
	Snake snake(&level1);


	while (!glfwWindowShouldClose(window))
	{
		//Timer
		Time.TimerUpdate();

		//Render
		glfwGetWindowSize(this->window, &this->width, &this->height);
		glfwSwapBuffers(window);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		level1.FrameCycle();

		//InputUpdate
		Input::InputUpdate();

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

	//Register call back
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
}
