#include "ReturnButton.h"
#include "StartScene.h"
#include "MainWindow.h"


ReturnButton::ReturnButton(Canvas *canvas)
	: Button(canvas)
{
	this->LoadTexture("UI/return.png");
	this->scale = glm::vec2(0.2, 0.1);
}


ReturnButton::~ReturnButton()
{
}

void ReturnButton::OnClick()
{
	MainWindow::Instance()->loadScene(new StartScene());
}
