#pragma once

#include"Transform.h"
#include"Model.h"
#include"Shader.h"
#include "GameObject.h"
#include "Camera.h"

#include<List>

class Scene
{
	friend void GameObject::Destroy(GameObject *gameObject);
	friend void GameObject::Render();
	friend GameObject::GameObject(Scene* scene, GameObject *parent);
	friend void Camera::Activate();

public:
	Scene();
	~Scene();

	void FrameCycle();

	//light
	void ApplicateLight(Shader &shader);
	void SetDirectedLight(glm::vec3 direction,glm::vec3 color);
	glm::vec3 GetLightDirection();
	glm::vec3 GetDirectedLightColor();
	glm::vec3 GetAmbientLightColor();

private:
	//Frame cycle
	void Enable();
	void Update();
	void Renrer();

	void RemoveObject(GameObject *gameObject);

private:
	std::list<GameObject*> ObjectList;			//The list of gameObject
	Camera *camera;								//The active camera			

	glm::vec3 lightDirection;					//The direction of directed light
	glm::vec3 directedLightColor;				//The color of directed light
	glm::vec3 ambientLightColor;				//The color of ambient light

};
