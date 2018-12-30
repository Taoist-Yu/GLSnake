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

//Single Instance Mode
private:
	static MainWindow* windowInstance;
public:
	static void CreateInstance();
	static void CreateInstance(GLuint width, GLuint height, std::string title);
	static MainWindow* Instance();

//Event Function
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//Input Event
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

public:
	~MainWindow();
	void MainLoop();

	int GetWidth();
	int GetHeight();
	void QuitWindow();

	void loadScene(Scene * scene);
	
public:
	Scene* scene;			//Current active scene

private:
	MainWindow();
	MainWindow(GLuint width, GLuint height, std::string title);
	void WindowInit(GLuint width, GLuint height, std::string title);
	void loadScene();

private:
	int width;
	int height;
	std::string title;
	GLFWwindow* window;

	Scene *newScene = NULL;

};

