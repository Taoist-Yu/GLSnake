#include "Level1.h"



Level1::Level1()
{
	this->confine->SetColor(glm::vec4(0, 0.5, 0.5, 0.5));
	this->AttachSkybox(new Skybox("skybox/level1"));
}


Level1::~Level1()
{
}
