#pragma once
#include "GameObject.h"

class Confine :
	public GameObject
{
public:
	static const int radius;
public:
	Confine(Scene *scene, GameObject *parent = NULL);
	~Confine();

	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);

private:
	glm::vec4 color;
	void PreRender();

};

