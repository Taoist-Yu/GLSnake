#pragma once
#include "Scene.h"

#include "Snake.h"
#include "Food.h"
#include "Confine.h"

class Level :
	public Scene
{
public:
	Level();
	virtual ~Level();

protected:
	void Postcycle();


	void FoodDetection(GameObject* collider);
	void SnakeBodyDetection(GameObject* collider);

protected:
	Confine* confine;
	Snake* snake;
	Food* food;

	const SnakeNode* head;
	
};

