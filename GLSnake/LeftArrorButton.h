#pragma once
#include "Button.h"
class LeftArrorwButton :
	public Button
{
public:
	LeftArrorwButton(Canvas *canvas);
	~LeftArrorwButton();

	void OnClick();
};

