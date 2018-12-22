#include "Input.h"

std::set<int> Input::KeyDownSet;
std::set<int> Input::KeyRepeatSet;
std::set<int> Input::KeyUpSet;

bool Input::GetKeyDown(int keyCode)
{
	if (KeyDownSet.find(keyCode) != KeyDownSet.end())
		return true;
	else
		return false;
}

bool Input::GetKeyRepeat(int keyCode)
{
	if (KeyRepeatSet.find(keyCode) != KeyRepeatSet.end())
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

bool Input::GetKey(int keyCode)
{
	return GetKeyDown(keyCode) || GetKeyRepeat(keyCode);
}

void Input::InputUpdate()
{
	KeyDownSet.clear();
	KeyRepeatSet.clear();
	KeyUpSet.clear();
}
