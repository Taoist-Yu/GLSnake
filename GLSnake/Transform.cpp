#include "Transform.h"
#include "GameObject.h"


Transform::Transform(GameObject *gameObject)
	: gameObject(gameObject)
{
	if (gameObject->parent == NULL) {
		this->parent = NULL;
	}
	else {
		this->parent = &gameObject->parent->transform;
	}
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
}


Transform::~Transform()
{
}

glm::mat4 Transform::ModelMatrix()
{
	return GetTranslateMat() * GetRotationMat() * GetScaleMat();
}

glm::mat4 Transform::ModelInverse()
{
	return GetScaleInverse() * GetRotationInverse() * GetTranslateInverse();
}

void Transform::Translate(float x, float y, float z)
{
	this->position = this->position + glm::vec3(x, y, z);
}

void Transform::Rotate(float x, float y, float z)
{
	this->rotation = this->rotation + glm::vec3(x, y, z);
}

void Transform::Scale(float x, float y, float z)
{
	this->scale = this->scale * glm::vec3(x, y, z);
}

void Transform::Translate(glm::vec3 _translate)
{
	this->Translate(_translate.x, _translate.y, _translate.z);
}

void Transform::Rotate(glm::vec3 _rotation)
{
	this->Rotate(_rotation.x, _rotation.y, _rotation.z);
}

void Transform::Scale(glm::vec3 _scale)
{
	this->Scale(_scale.x, _scale.y, _scale.z);
}

void Transform::SetLocalPosition(float x, float y, float z)
{
	this->position = glm::vec3(x, y, z);
}

void Transform::SetLocalRotation(float x, float y, float z)
{
	this->rotation = glm::vec3(x, y, z);
}

void Transform::SetLocalScale(float x, float y, float z)
{
	this->scale = glm::vec3(x, y, z);
}

void Transform::SetLocalPosition(glm::vec3 _position)
{
	this->position = _position;
}

void Transform::SetLocalRotation(glm::vec3 _rotation)
{
	this->rotation = _rotation;
}

void Transform::SetLocalScale(glm::vec3 _scale)
{
	this->scale = _scale;
}

void Transform::SetPosition(float x, float y, float z)
{
	SetPosition(glm::vec3(x, y, z));
}

void Transform::SetRotation(float x, float y, float z)
{
	SetRotation(glm::vec3(x, y, z));
}

void Transform::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}

void Transform::SetPosition(glm::vec3 _position)
{
	if (parent == NULL) {
		SetLocalPosition(_position);
	}
	else {
		position = glm::vec3(
			parent->ModelInverse() *
			glm::vec4(_position, 1.0f)
		);
	}
}

void Transform::SetRotation(glm::vec3 _rotation)
{
	if (parent == NULL) {
		SetLocalRotation(_rotation);
	}
	else {
		rotation = _rotation - parent->GetRotationVec();
	}
}

void Transform::SetScale(glm::vec3 _scale)
{
	if (parent == NULL) {
		SetLocalScale(_scale);
	}
	else {
		scale.x = _scale.x / parent->GetScaleVec().x;
		scale.y = _scale.y / parent->GetScaleVec().y;
		scale.z = _scale.z / parent->GetScaleVec().z;
	}
}

glm::vec3 Transform::GetLoaclPositionVec()
{
	return this->position;
}

glm::vec3 Transform::GetLocalRotationVec()
{
	return this->rotation;
}

glm::vec3 Transform::GetLocalScaleVec()
{
	return this->scale;
}

glm::vec3 Transform::GetPositionVec()
{
	if (parent == NULL) {
		return GetLoaclPositionVec();
	}
	return glm::vec3(
		parent->ModelMatrix() *
		glm::vec4(this->GetLoaclPositionVec(), 1.0f)
	);
}

glm::vec3 Transform::GetRotationVec()
{
	if (parent == NULL) {
		return GetLocalRotationVec();
	}
	else {
		return GetLocalRotationVec() + parent->GetRotationVec();
	}
}

glm::vec3 Transform::GetScaleVec()
{
	if (parent == NULL) {
		return GetLocalScaleVec();
	}
	else {
		return GetLocalScaleVec() * parent->GetScaleVec();
	}
}

glm::mat4 Transform::GetTranslateMat()
{
	return glm::translate(glm::mat4(1), GetPositionVec());
}

glm::mat4 Transform::GetRotationMat()
{
	glm::mat4 matrix(1);
	matrix = glm::rotate(matrix, glm::radians(GetRotationVec().x), glm::vec3(1, 0, 0));		//x axis
	matrix = glm::rotate(matrix, glm::radians(GetRotationVec().y), glm::vec3(0, 1, 0));		//y axis
	matrix = glm::rotate(matrix, glm::radians(GetRotationVec().z), glm::vec3(0, 0, 1));		//z axis
	return matrix;
}

glm::mat4 Transform::GetScaleMat()
{
	return glm::scale(glm::mat4(1),GetScaleVec());
}

glm::mat4 Transform::GetTranslateInverse()
{
	return glm::translate(glm::mat4(1), -GetPositionVec());
}

glm::mat4 Transform::GetRotationInverse()
{
	glm::mat4 matrix(1);
	matrix = glm::rotate(matrix, glm::radians(-GetRotationVec().x), glm::vec3(1, 0, 0));		//x axis
	matrix = glm::rotate(matrix, glm::radians(-GetRotationVec().y), glm::vec3(0, 1, 0));		//y axis
	matrix = glm::rotate(matrix, glm::radians(-GetRotationVec().z), glm::vec3(0, 0, 1));		//z axis
	return matrix;
}

glm::mat4 Transform::GetScaleInverse()
{
	glm::vec3 inverseScale(
		1 / GetScaleVec().x,
		1 / GetScaleVec().y,
		1 / GetScaleVec().z
	);
	return glm::scale(glm::mat4(1), inverseScale);
}
