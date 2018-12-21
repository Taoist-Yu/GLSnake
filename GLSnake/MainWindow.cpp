#include "MainWindow.h"

#include<iostream>

#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"

#include "Ball.h"

void MainWindow::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
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
	Shader shader("shader.vert", "shader.frag");
	Scene scene;
	GameObject human(&scene, "model/nanosuit/nanosuit.obj", shader);
	GameObject plane(&scene, "model/GrassPlane/Grass.obj", shader);
	Ball ball(&scene);
	Camera camera(&scene,&human);

	plane.transform.Scale(100, 1, 100);
	plane.transform.Translate(0, -0.5f, 0);
	ball.transform.Translate(-3, 2, 0);
	camera.transform.Translate(0, 20, 20);
	camera.transform.Rotate(-30, 0, 0);

	camera.Update();
	camera.Activate();

	while (!glfwWindowShouldClose(window))
	{
		//Timer
		Time.TimerUpdate();

		//Render
		glfwGetWindowSize(this->window, &this->width, &this->height);
		glfwSwapBuffers(window);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.aspectRatio = (float)this->width / (float)this->height;
		scene.FrameCycle();

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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
