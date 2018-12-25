#pragma once

#include"Transform.h"
#include"Model.h"
#include"Shader.h"
#include "GameObject.h"
#include "Camera.h"
#include "Skybox.h"

#include<List>

class Scene
{
	friend void GameObject::Destroy(GameObject *gameObject);
	friend void GameObject::Render();
	friend GameObject::GameObject(Scene* scene, GameObject *parent);
	friend void Camera::Activate();

public:
	enum GameStatus {
		normal,
		pause
	};

	Scene();
	~Scene();

	void Activate();
	void FrameCycle();

	//light
	void ApplicateLight(Shader &shader);
	void SetDirectedLight(glm::vec3 direction,glm::vec3 color);
	glm::vec3 GetLightDirection();
	glm::vec3 GetDirectedLightColor();
	glm::vec3 GetAmbientLightColor();

	//Status
	void SetStatus(GameStatus status);
	GameStatus GetStatus();

	//
	void AttachSkybox(Skybox *skybox);

protected:
	//Frame cycle
	void Enable();
	void Update();
	void Renrer();
	virtual void Postcycle();

	void RemoveObject(GameObject *gameObject);

public:
	float timeScale = 1;

protected:

	GameStatus status = normal;

	std::list<GameObject*> ObjectList;			//The list of gameObject
	Camera *camera;								//The active camera	

	glm::vec3 lightDirection;					//The direction of directed light
	glm::vec3 directedLightColor;				//The color of directed light
	glm::vec3 ambientLightColor;				//The color of ambient light

};

