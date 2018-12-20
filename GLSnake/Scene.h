#pragma once

#include"Transform.h"
#include"Model.h"
#include"Shader.h"
#include "GameObject.h"
#include "Camera.h"

#include<List>

class Scene
{
//ÓÑÔªÉùÃ÷
	friend void GameObject::Destroy(GameObject *gameObject);
	friend void GameObject::Render();
	friend GameObject::GameObject(Scene* scene, GameObject *parent);
	friend void Camera::Activate();

public:
	Scene();
	~Scene();

	void FrameCycle();

private:
	//Frame cycle
	void Enable();
	void Update();
	void Renrer();

	void RemoveObject(GameObject *gameObject);

private:
	std::list<GameObject*> ObjectList;			//The list of gameObject
	Camera *camera;								//The active camera
};

