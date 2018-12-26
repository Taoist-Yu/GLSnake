#include "Bomb.h"
#include "Level.h"
#include "Time.h"

Bomb::Bomb(Scene *scene, GameObject *parent)
	: Ball(scene, parent)
{
	this->tag = Tag::bomb;
	this->SetColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
}

Bomb::~Bomb()
{
}

void Bomb::OnEnable()
{
	glm::vec3 pos = Level::ObjectRespawnPosition(scene);
	this->transform.SetPosition(pos);
}

void Bomb::Respawn()
{
	this->SetActive(false);
	this->SetActive(true);
}
