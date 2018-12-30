#pragma once
#include "Canvas.h"
#include "ExitButton.h"
#include "StartButton.h"
#include "LeftArrorButton.h"
#include "RightArrowButton.h"
#include "DifficultyButton.h"
#include "ContinueButton.h"

class StartCanvas :
	public Canvas
{
public:
	StartCanvas(Scene* scene);
	~StartCanvas();

	void PostUpdate();

protected:
	StartButton* start;
	ExitButton* exit;
	LeftArrorwButton* left;
	RightArrowButton* right;
	DifficultyButton* difficulty;
	ContinueButton*   continueButton;

};

