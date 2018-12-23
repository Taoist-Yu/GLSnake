#pragma once
#include "GameObject.h"
#include "SnakeNode.h"
#include "Camera.h"

/*The snake manager
**All snake head and snake bodies would be attached to Snake 
*/
class Snake :
	public GameObject
{
public:
	Snake(Scene *scene, GameObject *parent = NULL);
	~Snake();
	
	int GetLength();
	void Incress();
	void Decress();

	void ActivateCamera();

private:
	void InitSnake();
	void ChangeHead(SnakeNode* newHead);
	void Update();

private:
	Camera* camera;			//Camera will follow snake head
	SnakeNode* head;
	SnakeNode* tail;
	glm::vec3 direction;
	int length;
	float speed;			//Move speed of the snake
	float sensitivity;		//The speed of changing view

	const float spacing = 1.0f;
	const glm::vec3 headColor = glm::vec3(1, 0, 0);
	const glm::vec3 bodyColor = glm::vec3(0, 1, 1);
	
};

