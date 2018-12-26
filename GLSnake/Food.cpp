#include "Food.h"

#include "Random.h"
#include "Confine.h"
#include "Level.h"

Food::Food(Scene *scene, GameObject *parent)
	: Ball(scene, parent)
{
	
}


Food::~Food()
{
}

void Food::Respawn()
{
	this->SetActive(false);
	this->SetActive(true);
}

void Food::Update()
{
	glm::vec3 v = transform.GetPositionVec();
	float dis = glm::distance(v, glm::vec3(0, 0, 0));

	if (dis > ((Level*)scene)->GetCurrentRadius()) {
		this->transform.SetPosition(this->transform.GetPositionVec() / 2.0f);
	}
}

void Food::OnEnable()
{
	tag = Tag::food;
	SetColor(glm::vec4(1, 1, 0, 1));

	this->transform.SetPosition(Level::ObjectRespawnPosition(scene));
}
