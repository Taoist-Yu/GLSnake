#include "Scene.h"



Scene::Scene()
{

}

Scene::~Scene()
{
}

void Scene::Update()
{
	for (GameObject* object : ObjectList) {
		object->LifeCycle();
	}
}

void Scene::ConfigShader(Shader & shader)
{
	camera->ConfigShader(shader);
}

void Scene::DeleteObject(GameObject * gameObject)
{
	for (GameObject *object : ObjectList) {
		if (object == gameObject) {
			ObjectList.remove(object);
			break;
		}
	}
}
