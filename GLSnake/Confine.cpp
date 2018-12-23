#include "Confine.h"



Confine::Confine(Scene *scene, GameObject *parent)
	: GameObject(scene, "model/Confine/Confine.obj", "confine.vert", "confine.frag", parent)
{
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
}

void Confine::PreRender()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
