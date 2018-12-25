#include "Input.h"

std::set<int> Input::KeyDownSet;
std::set<int> Input::KeySet;
std::set<int> Input::KeyUpSet;
glm::vec2 Input::MouseMove;

bool Input::GetKeyDown(int keyCode)
{
	if (KeyDownSet.find(keyCode) != KeyDownSet.end())
		return true;
	else
		return false;
}

bool Input::GetKey(int keyCode)
{
	if (KeySet.find(keyCode) != KeySet.end())
		return true;
	else
		return false;
}

bool Input::GetKeyUp(int keyCode)
{
	if (KeyUpSet.find(keyCode) != KeyUpSet.end())
		return true;
	else
		return false;
}

glm::vec2 Input::GetMouseMove()
{
	return MouseMove;
}

void Input::InputUpdate()
{
	KeyDownSet.clear();
	KeyUpSet.clear();
	MouseMove = glm::vec2(0, 0);
}
