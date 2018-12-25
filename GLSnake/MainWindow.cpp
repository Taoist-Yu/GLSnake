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
#include "Skybox.h"

MainWindow* MainWindow::windowInstance;

void MainWindow::CreateInstance()
{
	if(windowInstance == NULL)
		windowInstance = new MainWindow();
}

void MainWindow::CreateInstance(GLuint width, GLuint height, std::string title)
{
	if(windowInstance == NULL)
		windowInstance = new MainWindow(width, height, title);
}

MainWindow* MainWindow::Instance()
{
	return windowInstance;
}

void MainWindow::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MainWindow::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		Input::KeyDownSet.insert(key);
		Input::KeySet.insert(key);
	}
	if (action == GLFW_RELEASE) {
		Input::KeyUpSet.insert(key);
		Input::KeySet.erase(key);
	}
}

void MainWindow::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	static double lastX = -1;
	static double lastY = -1;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (xoffset > 50)xoffset = 0;
	if (yoffset > 50)yoffset = 0;

	Input::MouseMove = glm::vec2(xoffset, yoffset);
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
	level1.Activate();
	//Level1
//	Confine confine(&level1);
	Snake snake(&level1);
//	confine.SetColor(glm::vec4(0, 1, 1, 1));
	level1.AttachSkybox(new Skybox("Skybox/Level1"));
	level1.timeScale = 1;

	while (!glfwWindowShouldClose(window))
	{
		//Timer
		Time.TimerUpdate();

		//Render
		glfwGetWindowSize(this->window, &this->width, &this->height);
		glfwSwapBuffers(window);
		glClearColor(0.05f, 0.5f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->scene->FrameCycle();

		//Escape Input
		if (Input::GetKeyDown(GLFW_KEY_ESCAPE)) {
			if (scene->GetStatus() == Scene::normal) {
				scene->SetStatus(Scene::pause);
				Time.SetTimeScale(0);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else if (scene->GetStatus() == Scene::pause) {
				scene->SetStatus(Scene::normal);
				Time.SetTimeScale(scene->timeScale);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
		}

		//InputUpdate
		Input::InputUpdate();
		glfwPollEvents();
	}
}

int MainWindow::GetWidth()
{
	return width;
}

int MainWindow::GetHeight()
{
	return height;
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
	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
