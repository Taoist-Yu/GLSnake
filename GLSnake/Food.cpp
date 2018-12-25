#include "Food.h"

#include "Random.h"
#include "Confine.h"

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

void Food::OnEnable()
{
	tag = Tag::food;
	SetColor(glm::vec4(1, 1, 0, 1));

	glm::vec3 Pos(Random::Range(-1, 1), Random::Range(-1, 1), Random::Range(-1, 1));
	Pos = normalize(Pos);
	Pos = Random::Range(0, Confine::radius - 2) * Pos;		//食物不在边界生成
	this->transform.SetPosition(Pos);
}
