#include "Snake.h"
#include "Time.h"
#include "Scene.h"

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
		offset = -direction * spacing;
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
	if (length == 1) {
		//Unfinished!!!
		//Destroy Snake
	}
	else {
		SnakeNode* oldHead = head;
		ChangeHead(head->next);
		delete oldHead;
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
	for (int i = 0; i < 3; i++) {
		this->Incress();
	}
}

void Snake::ChangeHead(SnakeNode* head)
{
	this->head = head;
	if (camera == NULL) {
		camera = new Camera(scene, head);
	}
	else {
		camera->SetParent(head);
	}

	camera->transform.SetLocalPosition(0, 3, 3);
	camera->transform.SetLocalRotation(0, 0, 0);
}

void Snake::Update()
{
	//Traverse all snake node and change position
	SnakeNode *p = head;
	while (p->next != NULL) {
		p = p->next;
		p->transform.SetPosition(p->last->transform.GetPositionVec());
	}
	//Move the head
	head->transform.Translate(direction * speed * Time.GetDeltaTime());
}
