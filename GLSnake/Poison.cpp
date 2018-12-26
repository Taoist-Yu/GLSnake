#include "Poison.h"
#include "Random.h"
#include "Confine.h"
#include "Level.h"
#include "Time.h"
#include<math.h>

Poison::Poison(Scene *scene, GameObject* parent)
	: Ball(scene,parent)
{
	delete shader;
	shader = new Shader("poison.vert", "poison.frag");
	tag = Tag::poison;
}

Poison::~Poison()
{
}

void Poison::OnEnable()
{
	glm::vec3 pos = Level::ObjectRespawnPosition(scene);
	this->transform.SetPosition(pos);
	timeVal = 0;
	unscaledTimeVal = 0;
}

void Poison::Update()
{
	timeVal += Time.GetDeltaTime();
	unscaledTimeVal += Time.GetUnscaledDeltaTime();
	//Ïú»Ù
	if (timeVal > 10) {
		SetActive(false);
	}
	else {
		//ÉÁË¸
		if ((int)(unscaledTimeVal * 10) % 2) {
			this->EnableRendering();
		}
		else {
			this->DisableRendring();
		}
		//Ðý×ª
		transform.SetRotation(
			360 * sin(unscaledTimeVal),
			360 * cos(unscaledTimeVal),
			360 * sin(unscaledTimeVal + glm::radians(45.f))
		);
	}
}
