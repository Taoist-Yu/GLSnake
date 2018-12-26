#include "Level2.h"
#include "Time.h"


Level2::Level2()
{
	this->confine->SetColor(glm::vec4(0.5f, 0.5f, 0.6f, 1.0f));
	this->AttachSkybox(new Skybox("skybox/level2"));
}

Level2::~Level2()
{
}

void Level2::PostcycleEX()
{
	if (GetCurrentRadius() > 20) {
		confine->SetCurrentRadius(GetCurrentRadius() - Time.GetDeltaTime());
	}
}
