#include "RightArrowButton.h"
#include "GameData.h"


RightArrowButton::RightArrowButton(Canvas *canvas)
	: Button(canvas)
{
	LoadTexture("UI/rArror.png");
	this->scale = glm::vec2(0.1, 0.1);
	this->position = glm::vec2(0.8, 0);
}


RightArrowButton::~RightArrowButton()
{
}

void RightArrowButton::OnClick()
{
	GameData::currentLevel++;
	if (GameData::currentLevel > 3)GameData::currentLevel = 1;
}
