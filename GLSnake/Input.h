#pragma once

#include<set>

#include "MainWindow.h"

class Input
{
	friend void MainWindow::WindowInit(GLuint width, GLuint height, std::string title);
	friend void MainWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void MainWindow::cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

public:
	static bool GetKeyDown(int keyCode);
	static bool GetKey(int keyCode);
	static bool GetKeyUp(int keyCode);
	static glm::vec2 GetMouseMove();

	static void InputUpdate();

private:
	static std::set<int> KeyDownSet;
	static std::set<int> KeySet;
	static std::set<int> KeyUpSet;
	static glm::vec2 MouseMove;

};

