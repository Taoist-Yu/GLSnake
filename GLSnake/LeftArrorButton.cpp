#include "LeftArrorButton.h"
#include "GameData.h"


LeftArrorwButton::LeftArrorwButton(Canvas *canvas)
	: Button(canvas)
{
	LoadTexture("UI/lArror.png");
	this->scale = glm::vec2(0.1, 0.1);
	this->position = glm::vec2(-0.8, 0);
}


LeftArrorwButton::~LeftArrorwButton()
{
}

void LeftArrorwButton::OnClick()
{
	GameData::currentLevel--;
	if (GameData::currentLevel == 0)GameData::currentLevel = 3;
}
