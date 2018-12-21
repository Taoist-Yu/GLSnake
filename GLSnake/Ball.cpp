#include "Ball.h"


Ball::Ball(Scene * scene, GameObject * parent)
	: GameObject(scene, "model/Ball/Ball.obj", "ball.vert", "ball.frag", parent)
{
	color = glm::vec4(1,1,1,1);
}

Ball::~Ball()
{
}

glm::vec4 Ball::GetColor()
{
	return this->color;
}

void Ball::SetColor(glm::vec4 color)
{
	this->color = color;
}

void Ball::PreRender()
{
	shader->SetVec4("color", this->color);
}
