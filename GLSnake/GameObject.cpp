#include "GameObject.h"

#include "Scene.h"
#include"Debug.h"

void GameObject::Destroy(GameObject * gameObject)
{
	for (GameObject *object : gameObject->childrenList) {
		Destroy(object);
	}
	gameObject->SetParent(NULL);
	gameObject->scene->DeleteObject(gameObject);
	//Delete the dynamic memory applied by the new operator
	delete gameObject->model;
}

GameObject::GameObject(Scene * scene, GameObject * parent)
	: transform(this)
{
	this->scene = scene;
	SetParent(parent);
	scene->ObjectList.push_back(this);
}

void GameObject::LifeCycle()
{
	Update();
	if (tag != camera)
	{
		Render();
	}
		
}

void GameObject::Render()
{
	shader.SetMat4("model", transform.ModelMatrix());
	scene->ConfigShader(shader);
	model->Draw(shader);
}


GameObject::GameObject(Scene* scene, const char *modelPath, GameObject *parent)
	: GameObject(scene, parent)
{
	model = new Model(modelPath);
}

GameObject::GameObject(Scene * scene, const char *modelPath, Shader & shader, GameObject *parent)
	: GameObject(scene, modelPath, parent)
{
	this->SetShader(shader);
}

GameObject::GameObject(Scene * scene, const char *modelPath, const char * vShaderFile, const char * fShaderFile, GameObject *parent)
	: GameObject(scene, modelPath, parent)
{
	this->SetShader(vShaderFile, fShaderFile);
}

GameObject::~GameObject()
{
	Destroy(this);
}

void GameObject::SetShader(Shader & shader)
{
	this->shader = shader;
}

void GameObject::SetShader(const char * vShaderFile, const char * fShaderFile)
{
	this->shader = Shader(vShaderFile, fShaderFile);
}

void GameObject::SetParent(GameObject * parent)
{
	//Unbind the current parent
	if (this->parent != NULL)
	{
		this->parent->DeleteChild(this);
	}
	//Bind new parent
	this->parent = parent;
	if (parent != NULL) {
		this->transform.parent = &parent->transform;
		parent->childrenList.push_back(this);
	} else {
		this->transform.parent = NULL;
	}

}

void GameObject::DeleteChild(GameObject * child)
{
	bool flag = false;
	for (GameObject* _child : this->childrenList) {
		if (_child == child) {
			flag = true;
			_child->parent = NULL;
			childrenList.remove(_child);
			break;
		}
	}
	if (flag == false) {
		Debug::Error("You are trying to delete a inexistent child");
	}

}

void GameObject::Update()
{
	
}

