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

	void SetCurrentRadius(int currentRadius);
	int GetCurrentRaduis();

	void Update();
	void OnEnable();

private:
	glm::vec4 color;
	void PreRender();

	int currentRadius;			//缩圈过程中当前半径

};

