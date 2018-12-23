#include "SnakeNode.h"



SnakeNode::SnakeNode(Scene *scene, GameObject *parent)
	: Ball(scene, parent)
{
	next = NULL;
	last = NULL;
}


SnakeNode::~SnakeNode()
{
}
