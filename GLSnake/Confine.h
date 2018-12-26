#pragma once
#include "GameObject.h"

class Confine :
	public GameObject
{
public:
	static const float radius;

public:
	Confine(Scene *scene, GameObject *parent = NULL);
	~Confine();

	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);

	void SetCurrentRadius(float currentRadius);
	float GetCurrentRaduis();

	void Update();
	void OnEnable();

private:
	glm::vec4 color;
	void PreRender();

	float currentRadius;			//缩圈过程中当前半径

};

