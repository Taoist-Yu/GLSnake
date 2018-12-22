#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<string>
#include<fstream>
#include<list>

#include "GameObject.h"

class MainWindow
{
	friend class Input;
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//Input Event
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	MainWindow();
	MainWindow(GLuint width, GLuint height, std::string title);
	~MainWindow();

	void MainLoop();

public:
	std::list<GameObject*>Observers;

private:
	int width;
	int height;
	std::string title;
	GLFWwindow* window;

	void WindowInit(GLuint width, GLuint height, std::string title);

};

