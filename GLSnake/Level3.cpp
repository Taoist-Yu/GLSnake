#include "Level3.h"
#include "Time.h"


Level3::Level3()
{
	this->confine->SetColor(glm::vec4(0.3f, 0.0f, 0.0f, 1.0f));
	this->AttachSkybox(new Skybox("skybox/level3"));

	meteorolites[0] = new Meteorolite(this);
	meteorolites[0]->transform.SetPosition(70, 0, 0);
	meteorolites[0]->transform.SetScale(12, 12, 12);
	meteorolites[1] = new Meteorolite(this);
	meteorolites[1]->transform.SetPosition(0, 20, 0);
	meteorolites[1]->transform.SetScale(5, 5, 5);
}


Level3::~Level3()
{

}

void Level3::PostcycleEX()
{
	if (GetCurrentRadius() > 20) {
		confine->SetCurrentRadius(GetCurrentRadius() - Time.GetDeltaTime());
	}

	glm::vec3 pos;
	glm::mat4 rotation;
	//Meteorolite 0
	rotation = glm::rotate(glm::mat4(1), Time.GetDeltaTime() / 10, glm::vec3(0, 1, 0));
	pos = rotation * glm::vec4(meteorolites[0]->transform.GetPositionVec(), 1.0f);
	meteorolites[0]->transform.SetPosition(pos);
	//Meteorolite 1
	rotation = glm::rotate(glm::mat4(1), Time.GetDeltaTime() / 2, glm::vec3(1, 0, 0));
	pos = rotation * glm::vec4(meteorolites[1]->transform.GetPositionVec(), 1.0f);
	meteorolites[1]->transform.SetPosition(pos);
}