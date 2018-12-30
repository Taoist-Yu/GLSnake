#pragma once
#include "Button.h"
class ExitButton :
	public Button
{
public:
	ExitButton(Canvas* canvas);
	~ExitButton();

	void OnClick();
};

