#include "Snake.h"
#include "Time.h"
#include "Scene.h"
#include "Input.h"
#include<iostream>

Snake::Snake(Scene *scene, GameObject *parent)
	: GameObject(scene, parent)
{
	tag = Tag::emptyObject;
	DisableRendring();
	InitSnake();
	this->ActivateCamera();
}


Snake::~Snake()
{
}

int Snake::GetLength()
{
	return length;
}

void Snake::Incress()
{
	SnakeNode* newTail = new SnakeNode(scene, this);
	newTail->last = tail;
	tail->next = newTail;

	//newTail相对与tail的位移
	glm::vec3 offset;
	if (length == 1) {
		offset = -glm::vec3(head->transform.GetRotationMat() * glm::vec4(0,0,-1,1)) * spacing;
	}
	else {
		offset = tail->transform.GetPositionVec() - tail->last->transform.GetPositionVec();
		//Avoid accumulative error
		offset = glm::normalize(offset);
		offset *= spacing;
	}

	//Set new position
	newTail->transform.SetPosition(offset + tail->transform.GetPositionVec());

	tail = newTail;
	tail->SetColor(glm::vec4(bodyColor, 1.0f));
	length++;
}

void Snake::Decress()
{
	if (length <= 1) {
		//Unfinished!!!
		//Destroy Snake
	}
	else {
		SnakeNode* oldTail = tail;
		tail = tail->last;
		tail->next = NULL;
		delete oldTail;
	}
	length--;
}

void Snake::ActivateCamera()
{
	camera->Activate();
}

void Snake::InitSnake()
{
	tail = new SnakeNode(scene, this);
	ChangeHead(tail);
	length = 1;
	for (int i = 0; i < 10; i++) {
		this->Incress();
	}
}

void Snake::ChangeHead(SnakeNode* head)
{
	this->head = head;
	head->last = NULL;
	head->tag = Tag::snakeHead;
	head->SetColor(glm::vec4(this->headColor, 1.0f));

	if (camera == NULL) {
		camera = new Camera(scene, head);
	}
	else {
		camera->SetParent(head);
	}

	camera->transform.SetLocalPosition(0, 16, 30);
	camera->transform.SetLocalRotation(-30, 0, 0);
}

void Snake::Update()
{
	//Input Handler
	if(scene->GetStatus() == Scene::normal)
	{
		if (Input::GetKey(GLFW_KEY_A)) {
			directionEuler.y += sensitivity * Time.GetDeltaTime();
		}
		if (Input::GetKey(GLFW_KEY_D)) {
			directionEuler.y -= sensitivity * Time.GetDeltaTime();
		}
		if (Input::GetKeyDown(GLFW_KEY_J)) {
			this->Incress();
		}
		if (Input::GetKeyDown(GLFW_KEY_K)) {
			this->Decress();
		}
		directionEuler.x += Input::GetMouseMove().y * sensitivity * Time.GetDeltaTime();
	}

	//Traverse all snake node and change position
	SnakeNode *p = tail;
	while (p->last != NULL) {
		glm::vec3 dir = p->last->transform.GetPositionVec() - p->transform.GetPositionVec();
		dir = glm::normalize(dir);
		p->transform.Translate(dir * speed * Time.GetDeltaTime());
		p = p->last;
	}
	//Move the head
	head->transform.SetRotation(directionEuler);
	head->transform.Translate(glm::vec3(0, 0, -1) * speed * Time.GetDeltaTime());

	//Traverse all snake node and normalize the spacing
	p = head;
	while (p->next != NULL) {
		p = p->next;
		glm::vec3 offset =  p->transform.GetPositionVec() - p->last->transform.GetPositionVec();
		offset = spacing * normalize(offset);
		p->transform.SetPosition(p->last->transform.GetPositionVec() + offset);
	}
	p = head;

}
