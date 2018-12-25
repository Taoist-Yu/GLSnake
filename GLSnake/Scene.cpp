#include "Scene.h"
#include "Time.h"
#include "MainWindow.h"

Scene::Scene()
{
	lightDirection = glm::vec3(0, -1, 0);
	directedLightColor = glm::vec3(1, 1, 1);
	ambientLightColor = glm::vec3(0.2, 0.2, 0.2);
}

Scene::~Scene()
{
}

void Scene::Activate()
{
	MainWindow::Instance()->scene = this;
	Time.SetTimeScale(timeScale);
}

void Scene::FrameCycle()
{
	float newAspectRatio = (float)MainWindow::Instance()->GetWidth() / (float)MainWindow::Instance()->GetHeight();
	if(newAspectRatio > 0)
		camera->aspectRatio = newAspectRatio;
	camera->DrawSky();
	Enable();
	Update();
	Renrer();
	Postcycle();
}

void Scene::ApplicateLight(Shader &shader)
{
	shader.SetVec3("lightDirection", lightDirection);
	shader.SetVec3("directedLightColor", directedLightColor);
	shader.SetVec3("ambientLightColor", ambientLightColor);
}

void Scene::SetDirectedLight(glm::vec3 direction, glm::vec3 color)
{
	lightDirection = direction;
	directedLightColor = color;
}

glm::vec3 Scene::GetLightDirection()
{
	return lightDirection;
}

glm::vec3 Scene::GetDirectedLightColor()
{
	return directedLightColor;
}

glm::vec3 Scene::GetAmbientLightColor()
{
	return ambientLightColor;
}

void Scene::SetStatus(GameStatus status)
{
	this->status = status;
}

Scene::GameStatus Scene::GetStatus()
{
	return this->status;
}

void Scene::AttachSkybox(Skybox * skybox)
{
	camera->AttachSkybox(skybox);
}

void Scene::Enable()
{
	for (GameObject* object : ObjectList) {
		if (object->isPreActive) {
			object->PreEnable();
			object->OnEnable();
		}
	}
}

void Scene::Update()
{
//	lightDirection = glm::rotate(glm::mat4(1), Time.GetDeltaTime(), glm::vec3(1, 0, 0)) * glm::vec4(GetLightDirection(),1.0f);
	for (GameObject* object : ObjectList) {
		if(object->GetActive())
			object->Update();
	}
}

void Scene::Renrer()
{
	for (GameObject* object : ObjectList) {
		if (object->isRendereringEnable && object->GetActive()) {
			object->PreRender();
			object->Render();
			object->PostRender();
		}
	}
}

void Scene::Postcycle()
{
}

void Scene::RemoveObject(GameObject * gameObject)
{
	for (GameObject *object : ObjectList) {
		if (object == gameObject) {
			ObjectList.remove(object);
			object->scene = NULL;
			break;
		}
	}
}
