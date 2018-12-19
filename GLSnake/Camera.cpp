#include "camera.h"
#include "Scene.h"

Camera::Camera(Scene *scene, GameObject *parent)
	: GameObject(scene, parent)
{
	tag = camera;
	Update();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	view = glm::mat4(1) *
		transform.GetScaleInverse() *
		transform.GetRotationInverse() *
		transform.GetPositionInverse();
	
	projection = glm::perspective(FOV, aspectRatio, nearPlane, farPlane);
}

void Camera::ConfigShader(Shader & shader)
{
	shader.Enable();
	shader.SetMat4("view", this->view);
	shader.SetMat4("projection", this->projection);
	shader.Disable();
}

void Camera::Activate()
{
	scene->camera = this;
}
