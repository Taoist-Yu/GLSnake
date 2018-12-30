#pragma once
#include "Button.h"

class DifficultyButton :
	public Button
{
public:
	DifficultyButton(Canvas *canvas);
	~DifficultyButton();

	void OnClick();

private:
	void UpdateDifficulty();
};

