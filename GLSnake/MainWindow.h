#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<string>
#include<fstream>

class MainWindow
{
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	MainWindow();
	MainWindow(GLuint width, GLuint height, std::string title);
	~MainWindow();

	void MainLoop();

private:
	int width;
	int height;
	std::string title;
	GLFWwindow* window;

	void WindowInit(GLuint width, GLuint height, std::string title);

};

