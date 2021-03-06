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
	delete skybox;
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

void Camera::AttachSkybox(Skybox * skybox)
{
	if (this->skybox != NULL) {
		delete this->skybox;
	}
	this->skybox = skybox;
}

void Camera::DrawSky()
{
	if (skybox != NULL) {
		//Render skybox
		skybox->Draw(view, projection);
	}
}

void Camera::CameraRender(Shader &shader)
{
	//Application the view matrix and the projection matrix
	shader.Enable();
	shader.SetMat4("view", this->view);
	shader.SetMat4("projection", this->projection);
	shader.Disable();
}
