#pragma once
#include "Ball.h"

class Bomb :
	public Ball
{
public:
	Bomb(Scene *scene, GameObject *parent = NULL);
	virtual ~Bomb();

	void OnEnable();
	void Respawn();

};

