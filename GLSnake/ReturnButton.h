#pragma once
#include "Button.h"

class ReturnButton :
	public Button
{
public:
	ReturnButton(Canvas *canvas);
	~ReturnButton();

	void OnClick();
};

