#include "camera.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"

Camera::Camera(Scene *scene, GameObject *parent)
	: GameObject(scene, parent)
{
	tag = camera;
	DisableRendring();
	Update();
}

Camera::~Camera()
{
}

void Camera::Update()
{	
	view = glm::mat4(1) *
		transform.GetRotationInverse() *
		transform.GetTranslateInverse();
	
	projection = glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane);
}

void Camera::Activate()
{
	scene->camera = this;
}

void Camera::CameraRender(Shader &shader)
{
	//Application the view matrix and the projection matrix
	shader.Enable();
	shader.SetMat4("view", this->view);
	shader.SetMat4("projection", this->projection);
	shader.Disable();
}
