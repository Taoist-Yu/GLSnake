#include "Level.h"



Level::Level()
{
	this->confine = new Confine(this);
	this->snake = new Snake(this);
	this->food = new Food(this);
}

Level::~Level()
{
}

void Level::Postcycle()
{
	head = snake->GetHead();
	//collision detection
	for (GameObject* object : ObjectList) {
		switch (object->tag)
		{
		case GameObject::Tag::snakeBody:
			SnakeBodyDetection(object);
			break;
		case GameObject::Tag::food:
			FoodDetection(object);
			break;
		default:
			break;
		}
	}
}

void Level::FoodDetection(GameObject * collider)
{
	float distance = glm::distance(collider->transform.GetPositionVec(), head->transform.GetPositionVec());
	if (distance < 2) {
		food->Respawn();
		snake->OnEatFood();
	}
}

void Level::SnakeBodyDetection(GameObject * collider)
{
	float distance = glm::distance(collider->transform.GetPositionVec(), head->transform.GetPositionVec());
	if (distance < 1.5) {
		snake->SetActive(false);
	}
}
