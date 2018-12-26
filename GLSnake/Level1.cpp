#include "Level1.h"



Level1::Level1()
{
	this->confine->SetColor(glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	this->AttachSkybox(new Skybox("skybox/level1"));
}


Level1::~Level1()
{
}
