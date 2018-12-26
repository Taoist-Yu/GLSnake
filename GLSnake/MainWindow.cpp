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
#include "Sprite.h"
#include "Text.h"

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

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

	if (xoffset > 30)xoffset = 0;
	if (yoffset > 30)yoffset = 0;

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//	Level3 level1;
//	level1.difficulty = Level::normal;
//	level1.timeScale = 10;
	Sprite sprite;
	sprite.scale = glm::vec2(0.2, 0.2);
	sprite.position = glm::vec2(0.5, 0.2);
	sprite.LoadTexture("container.jpg");
	Text text;
	text.SetText("8");

	while (!glfwWindowShouldClose(window))
	{
		//Timer
		Time.TimerUpdate();

		//Render
		glfwGetWindowSize(this->window, &this->width, &this->height);
		glfwSwapBuffers(window);
		glClearColor(0.05f, 0.5f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//		this->scene->FrameCycle();
 		sprite.Draw();
		text.Draw();

		//Escape Input
		if (Input::GetKeyDown(GLFW_KEY_ESCAPE)) {
			if (scene->GetStatus() == Scene::normal) {
				scene->SetStatus(Scene::pause);
				Time.SetTimeScale(0);
			}
			else if (scene->GetStatus() == Scene::pause) {
				scene->SetStatus(Scene::normal);
				Time.SetTimeScale(scene->timeScale);
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

}
