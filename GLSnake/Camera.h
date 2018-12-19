#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Shader.h"

class Camera : public GameObject
{
	friend class Scene;

public:
	//投影矩阵相关属性
	float FOV = 45.0f;
	float aspectRatio = 4 / 3;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

public:
	Camera(Scene *scene, GameObject *parent = NULL);
	~Camera();

	void Update();
	void ConfigShader(Shader &shader);
	void Activate();

private:
	glm::mat4 view;
	glm::mat4 projection;

};

