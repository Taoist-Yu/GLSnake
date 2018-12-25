#pragma once
#include "Ball.h"
class SnakeNode :
	public Ball
{
	friend class Snake;

public:
	SnakeNode(Scene *scene, GameObject *parent = NULL);
	~SnakeNode();

private:
	SnakeNode* next;
	SnakeNode* last;

};

