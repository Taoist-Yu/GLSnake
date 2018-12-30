#include "ContinueButton.h"



ContinueButton::ContinueButton(Canvas *canvas)
	: Button(canvas)
{
	this->LoadTexture("UI/continue.png");
	this->scale = glm::vec2(0.2, 0.1);
	this->position = glm::vec2(0, 0.3);
}


ContinueButton::~ContinueButton()
{
}
