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
		camera,
	};
	Tag tag = defaultObject;

public:
	GameObject(Scene* scene, const char *modelPath, GameObject *parent = NULL);
	GameObject(Scene* scene, const char *modelPath, Shader &shader, GameObject *parent = NULL);
	GameObject(Scene* scene, const char *modelPath, const char* vShaderFile, const char* fShaderFile, GameObject *parent = NULL);

	~GameObject();

	//Shader���
	void SetShader(Shader &shader);
	void SetShader(const char* vShaderFile, const char* fShaderFile);

	//����ĸ��ӹ�ϵ
	void SetParent(GameObject *parent);
	void DeleteChild(GameObject *child);

	virtual void Update();
	

protected:
	GameObject(Scene* scene, GameObject *parent = NULL);
	void LifeCycle();
	void Render();

public:
	Transform transform;

protected:
	Shader shader;
	Model *model;
	Scene *scene;								//ָ����Ϸ������ڵĳ���
	GameObject *parent;							//������ָ��
	std::list<GameObject*> childrenList;		//�Ӷ����б�
};

