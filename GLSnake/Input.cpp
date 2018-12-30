#include "Input.h"

std::set<int> Input::KeyDownSet;
std::set<int> Input::KeySet;
std::set<int> Input::KeyUpSet;
std::set<int> Input::mouseBottonDown;
std::set<int> Input::mouseBottonUp;
glm::vec2 Input::MouseMove;
glm::vec2 Input::MousePos;


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

bool Input::GetMouseBottonDown(int botton)
{
	if (mouseBottonDown.find(botton) != mouseBottonDown.end())
		return true;
	else
		return false;
}

bool Input::GetMouseBottonUp(int botton)
{
	if (mouseBottonUp.find(botton) != mouseBottonUp.end())
		return true;
	else
		return false;
}

glm::vec2 Input::GetMouseMove()
{
	return MouseMove;
}

glm::vec2 Input::GetMousePos()
{
	return MousePos;
}

void Input::InputUpdate()
{
	KeyDownSet.clear();
	KeyUpSet.clear();
	mouseBottonDown.clear();
	mouseBottonUp.clear();
	MouseMove = glm::vec2(0, 0);
}
