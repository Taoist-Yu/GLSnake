#pragma once
#include "Button.h"
class StartButton :
	public Button
{
public:
	StartButton(Canvas* canvas);
	~StartButton();

	void OnClick();
};

