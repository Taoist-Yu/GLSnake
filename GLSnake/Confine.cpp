#include "Confine.h"

const float Confine::radius = 100;

Confine::Confine(Scene *scene, GameObject *parent)
	: GameObject(scene, "model/Confine/Confine.obj", "confine.vert", "confine.frag", parent)
{
	transform.Scale(radius, radius, radius);
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

void Confine::SetCurrentRadius(float currentRadius)
{
	this->currentRadius = currentRadius;
}

float Confine::GetCurrentRaduis()
{
	return currentRadius;
}

void Confine::Update()
{
	this->transform.SetScale(currentRadius, currentRadius, currentRadius);
}

void Confine::OnEnable()
{
	this->currentRadius = radius;
}

void Confine::PreRender()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
