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
	void Rotate(float angle, glm::vec3(axis));

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
	glm::vec3 GetLoaclPositionVec() const;
	glm::vec3 GetLocalScaleVec() const;
	//Get transform vector in world space
	glm::vec3 GetPositionVec() const;
	glm::vec3 GetScaleVec() const; 

	//Get rotation mat in local space
	glm::mat4 GetLocalRotationMat() const;
	glm::mat4 GetLocalRotationInverse() const;

	//Get transform matrix in world space
	glm::mat4 GetTranslateMat() const;
	glm::mat4 GetRotationMat() const;
	glm::mat4 GetScaleMat() const;
	//Get transform inverse matrix in world space
	glm::mat4 GetTranslateInverse() const;
	glm::mat4 GetRotationInverse() const;
	glm::mat4 GetScaleInverse() const;

	//Get local axis in world space
	glm::vec3 GetX() const;
	glm::vec3 GetY() const;
	glm::vec3 GetZ() const;

protected:
	glm::vec3 position;
	glm::mat4 rotation;
	glm::vec3 scale;
};

