#include "ExitButton.h"
#include "MainWindow.h"


ExitButton::ExitButton(Canvas* canvas)
	: Button(canvas)
{
	LoadTexture("UI/exit.png");
	this->scale = glm::vec2(0.2, 0.1);
	this->position = glm::vec2(0, -0.5);
}

ExitButton::~ExitButton()
{
}

void ExitButton::OnClick()
{
	MainWindow::Instance()->QuitWindow();
}
