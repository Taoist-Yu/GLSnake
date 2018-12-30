#include "Button.h"
#include "Input.h"
#include "MainWindow.h"
#include "Canvas.h"

Button::Button(Canvas* canvas)
	: Sprite(canvas)
{
	this->canvas = canvas;
	canvas->bottonList.push_back(this);
}


Button::~Button()
{
}

void Button::Update()
{
	glm::vec2 pos = Input::GetMousePos();
	pos.x = pos.x / MainWindow::Instance()->GetWidth();
	pos.y = pos.y / MainWindow::Instance()->GetHeight();
	pos.x = pos.x * 2 - 1;
	pos.y = 1 - pos.y * 2;

	if (
		pos.x < position.x + scale.x &&
		pos.y < position.y + scale.y &&
		pos.x > position.x - scale.x &&
		pos.y > position.y - scale.y
		) {
		isSelected = true;
		color = glm::vec4(0.3, 0.3, 0.3, 1);
	}
	else {
		isSelected = false;
		isPressing = false;
		color = glm::vec4(1, 1, 1, 1);
	}
	
	if (Input::GetMouseBottonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		if (isSelected)isPressing = true;
	}
	if (Input::GetMouseBottonUp(GLFW_MOUSE_BUTTON_LEFT)) {
		if (isPressing)OnClick();
	}

}

void Button::OnClick()
{
}
