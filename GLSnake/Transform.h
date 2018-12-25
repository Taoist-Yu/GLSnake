#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject;

class Transform
{
friend class GameObject;

public:
	static glm::vec4 Rotate(glm::vec4 v, glm::vec3 axis, float angle);

public:
	GameObject *const gameObject;
	Transform * parent;

public:
	Transform(GameObject *gameObject);
	~Transform();

	glm::mat4 ModelMatrix();
	glm::mat4 ModelInverse();

	void Translate(float x,float y,float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Translate(glm::vec3 _translate);
	void Rotate(glm::vec3 _rotation);
	void Scale(glm::vec3 _scale);

	//Set transform in the local space
	void SetLocalPosition(float x, float y, float z);
	void SetLocalRotation(float x, float y, float z);
	void SetLocalScale(float x, float y, float z);
	void SetLocalPosition(glm::vec3 _position);
	void SetLocalRotation(glm::vec3 _rotation);
	void SetLocalScale(glm::vec3 _scale);

	//Set transform in the world space
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetPosition(glm::vec3 _position);
	void SetRotation(glm::vec3 _rotation);
	void SetScale(glm::vec3 _scale);

	//Get transform vector in local space 
	glm::vec3 GetLoaclPositionVec();
	glm::vec3 GetLocalRotationVec();
	glm::vec3 GetLocalScaleVec();
	//Get transform vertor in world space
	glm::vec3 GetPositionVec();
	glm::vec3 GetRotationVec();
	glm::vec3 GetScaleVec(); 

	//Get transform matrix in world space
	glm::mat4 GetTranslateMat();
	glm::mat4 GetRotationMat();
	glm::mat4 GetScaleMat();
	//Get transform inverse matrix
	glm::mat4 GetTranslateInverse();
	glm::mat4 GetRotationInverse();
	glm::mat4 GetScaleInverse();

protected:
	glm::vec3 GetX();
	glm::vec3 GetY();
	glm::vec3 GetZ();

protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

