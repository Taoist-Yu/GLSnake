#pragma once
#include "Scene.h"
#include<vector>

class StartScene :
	public Scene
{
public:
	StartScene();
	~StartScene();

	void setSky(int num);
	void Postcycle();

protected:
	int currentLevel;

};

