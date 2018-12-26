#pragma once
#include "Level.h"
#include "Meteorolite.h"


class Level3 :
	public Level
{
public:
	Level3();
	~Level3();

	void PostcycleEX();

protected:
	GameObject* meteorolites[2];

};

