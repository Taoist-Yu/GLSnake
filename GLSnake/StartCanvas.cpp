#include "StartCanvas.h"
#include "GameData.h"

StartCanvas::StartCanvas(Scene* scene)
	: Canvas(scene)
{
	start = new StartButton(this);
	exit = new ExitButton(this);
	left = new LeftArrorwButton(this);
	right = new RightArrowButton(this);
	difficulty = new DifficultyButton(this);
	continueButton = new ContinueButton(this);
	continueButton->SetActive(false);
}

StartCanvas::~StartCanvas()
{
	delete start;
	delete exit;
	delete left;
	delete right;
	delete difficulty;
	delete continueButton;
}

void StartCanvas::PostUpdate()
{
	if (GameData::currentLevel > GameData::levelUpper)
		start->SetActive(false);
	else
		start->SetActive(true);
}

