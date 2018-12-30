#include "StartButton.h"
#include "GameData.h"
#include "MainWindow.h"
#include "Levels.h"

StartButton::StartButton(Canvas* canvas)
	: Button(canvas)
{
	LoadTexture("UI/start.png");
	this->scale = glm::vec2(0.2, 0.1);
	this->position = glm::vec2(0, 0.5);
}


StartButton::~StartButton()
{
}

void StartButton::OnClick()
{
	if (GameData::currentLevel > GameData::levelUpper)
		return;
	switch (GameData::currentLevel)
	{
	case 1:
		MainWindow::Instance()->loadScene(new Level1());
		break;
	case 2:
		MainWindow::Instance()->loadScene(new Level2());
		break;
	case 3:
		MainWindow::Instance()->loadScene(new Level3());
		break;
	default:
		break;
	}
}
