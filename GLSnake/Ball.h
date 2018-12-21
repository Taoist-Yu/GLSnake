#pragma once
#include "GameObject.h"

class Ball :
	public GameObject
{
public:
	Ball(Scene *scene,GameObject *parent = NULL);
	~Ball();

	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);

private:
	glm::vec4 color;
	void PreRender();


};

