#pragma once
#include "Ball.h"

class Food :
	public Ball
{
public:
	Food(Scene *scene, GameObject *parent = NULL);
	virtual ~Food();

	void Respawn();
	void Update();

private:
	void OnEnable();
};

