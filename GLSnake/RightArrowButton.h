#pragma once
#include "Button.h"

class RightArrowButton :
	public Button
{
public:
	RightArrowButton(Canvas *Canvas);
	~RightArrowButton();

	void OnClick();

};

