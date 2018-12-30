#include "DifficultyButton.h"
#include "GameData.h"

DifficultyButton::DifficultyButton(Canvas *canvas)
	: Button(canvas)
{
	this->scale = glm::vec2(0.2, 0.1);
	UpdateDifficulty();
}


DifficultyButton::~DifficultyButton()
{
}

void DifficultyButton::OnClick()
{
	GameData::difficulty = (GameData::difficulty + 1) % 3;
	UpdateDifficulty();
}

void DifficultyButton::UpdateDifficulty()
{
	
	switch (GameData::difficulty) {
	case 0:
		this->LoadTexture("UI/easy.png");
		break;
	case 1:
		this->LoadTexture("UI/normal.png");
		break;
	case 2:
		this->LoadTexture("UI/hard.png");
		break;
	default:
		break;
	}
}
