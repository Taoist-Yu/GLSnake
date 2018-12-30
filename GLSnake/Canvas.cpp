#include "Canvas.h"



Canvas::Canvas(Scene* scene)
{
	this->scene = scene;
}


Canvas::~Canvas()
{
}

void Canvas::Update()
{
	for (auto object : bottonList) {
		if(object->GetActive())
			object->Update();
	}
	for (auto object : spriteList) {
		if(object->GetActive())
			object->Draw();
	}
	PostUpdate();
}

void Canvas::PostUpdate()
{
}


void Canvas::SetActive(bool active)
{
	this->isActive = active;
}

bool Canvas::GetActive()
{
	return this->isActive;
}
