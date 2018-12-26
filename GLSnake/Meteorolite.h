#pragma once
#include "GameObject.h"
class Meteorolite :
	public GameObject
{
public:
	Meteorolite(Scene* scene, GameObject* parent = NULL);
	~Meteorolite();

	void Update();

protected:
	float timeVal;
};

