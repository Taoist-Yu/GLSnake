#pragma once
#include "Sprite.h"

class Button :
	public Sprite
{
public:
	Button(Canvas* canvas);
	~Button();

	void Update();

	virtual void OnClick();

protected:
	bool isSelected;
	bool isPressing;

};

