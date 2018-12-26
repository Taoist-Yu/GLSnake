#pragma once
#include "Ball.h"

class Poison :
	public Ball
{
public:
	Poison(Scene *scene, GameObject *parent = NULL);
	virtual ~Poison();

	void OnEnable();

protected:
	void Update();

protected:
	float timeVal = 0;
	float unscaledTimeVal = 0;
};

