#include "Confine.h"



Confine::Confine(Scene *scene, GameObject *parent)
	: GameObject(scene, "model/Confine/Confine.obj", "confine.vert", "confine.frag", parent)
{
	transform.Scale(300, 300, 300);
}


Confine::~Confine()
{
}

glm::vec4 Confine::GetColor()
{
	return this->color;
}

void Confine::SetColor(glm::vec4 color)
{
	this->color = color;
	shader->SetVec4("color",color);
}

void Confine::PreRender()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
