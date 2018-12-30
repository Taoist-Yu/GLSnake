#pragma once
#include "Canvas.h"
#include "Level.h"
#include "ReturnButton.h"

class GameCanvas :
	public Canvas
{
	friend void Level::Postcycle();
	friend void Level::UpdateProcess();
public:
	GameCanvas(Scene *scene);
	~GameCanvas();

	void PostUpdate();

protected: 
	ReturnButton *returnButton;
	Sprite *headline;
	Sprite *processBar;
	Sprite *newLevel;
	Sprite *finish;

	float timeVal;
	
};

