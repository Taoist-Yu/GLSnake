#pragma once

#include<list>

#include"Transform.h"
#include"Model.h"
#include"Shader.h"

class Scene;

class GameObject
{
	friend class Transform;
	friend class Scene;

public:
	static void Destroy(GameObject *gameObject);

public:
	enum Tag
	{
		defaultObject,
		emptyObject,
		camera,
		snakeHead,
		snakeBody,
		food,
		poison,
		bomb,
	};
	Tag tag = defaultObject;

public:
	GameObject(Scene* scene, const char *modelPath, GameObject *parent = NULL);
	GameObject(Scene* scene, const char *modelPath, Shader &shader, GameObject *parent = NULL);
	GameObject(Scene* scene, const char *modelPath, const char* vShaderFile, const char* fShaderFile, GameObject *parent = NULL);

	virtual ~GameObject();

	//Shader相关
	void SetShader(Shader &shader);
	void SetShader(const char* vShaderFile, const char* fShaderFile);

	//对象的父子关系
	void SetParent(GameObject *parent);
	void DeleteChild(GameObject *child);

	//Activity
	void SetActive(bool active);
	bool GetActive();
	void EnableRendering();
	void DisableRendring();

protected:
	GameObject(Scene* scene, GameObject *parent = NULL);

	

	/*Lifecycle*/
	void PreEnable();
	//is called before the first Update() after activate
	virtual void OnEnable();
	//is called once per framed 
	virtual void Update();
	//is called before Renderer, you can do some extern configuration to your custom shader 
	virtual void PreRender();
	void Render();
	//is called after the camera finishes rendering the object
	virtual void PostRender();

public:
	Transform transform;

protected:
	Shader *shader;
	Model *model;
	Scene *scene;								//指向游戏对象存在的场景
	GameObject *parent;							//父对象指针
	std::list<GameObject*> childrenList;		//子对象列表

	/*Status variable*/
	bool isRendereringEnable = true;
	bool isPreActive = true;
	bool isActivity = true;

};

