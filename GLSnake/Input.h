#pragma once

#include<set>

#include "MainWindow.h"

class Input
{
	friend void MainWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	static bool GetKeyDown(int keyCode);
	static bool GetKeyRepeat(int keyCode);
	static bool GetKeyUp(int keyCode);
	static bool GetKey(int keyCode);

	static void InputUpdate();

private:
	static std::set<int> KeyDownSet;
	static std::set<int> KeyRepeatSet;
	static std::set<int> KeyUpSet;

};

