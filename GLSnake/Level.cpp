#include "Level.h"
#include "Random.h"
#include "Time.h"


glm::vec3 Level::ObjectRespawnPosition(Scene* scene)
{
	glm::vec3 Pos;
	bool flag = true;

	do {
		flag = true;
		Pos = glm::vec3(Random::Range(-1, 1), Random::Range(-1, 1), Random::Range(-1, 1));
		Pos = normalize(Pos);
		Pos = Random::Range(0, Confine::radius - 2) * Pos;		//对象不在边界生成
		for (GameObject* object : scene->ObjectList) {
			float distance = glm::distance(Pos, object->transform.GetPositionVec());
			if (distance < 3) {
				flag = false;
				break;
			}
		}
	} while (flag == false);

	return Pos;
}

Level::Level()
{
	this->confine = new Confine(this);
	this->snake = new Snake(this);
	this->food = new Food(this);

	for (int i = 0; i < 100;i++) {
		poisons[i] = new Poison(this);
		poisons[i]->SetActive(false);
	}

	for (int i = 0; i < 50; i++) {
		bombs[i] = new Bomb(this);
		bombs[i]->SetActive(false);
	}

	GameStart();

}

Level::~Level()
{
}

void Level::GameStart()
{
	switch (difficulty)
	{
	case Level::easy:
		poisonNum = 5;
		bombNum = 3;
		break;
	case Level::normal:
		poisonNum = 20;
		bombNum = 5;
		break;
	case Level::hard:
		poisonNum = 50;
		bombNum = 10;
		break;
	case Level::huaji:
		break;
	default:
		break;
	}

	//Poison
	GeneratePoison();

	//Bomb
	for (int i = 0; i < bombNum; i++) {
		bombs[i]->SetActive(true);
	}

	//Timer
	poisonTimeVal = 0;
	
	this->Activate();
}

void Level::GameOver()
{
	snake->SetActive(false);
}

float Level::GetCurrentRadius()
{
	return confine->GetCurrentRaduis();
}

void Level::Postcycle()
{
	if (snake->GetAlive() == false) {
		GameOver();
	}
	head = snake->GetHead();

	//Time
	poisonTimeVal += Time.GetDeltaTime();
	if (poisonTimeVal > 20) {
		poisonTimeVal = 0;
		GeneratePoison();
	}

	//collision detection
	ConfineDetection();
	for (GameObject* object : ObjectList) {
		if (object->GetActive()) {
			switch (object->tag)
			{
			case GameObject::Tag::snakeBody:
				SnakeBodyDetection(object);
				break;
			case GameObject::Tag::food:
				FoodDetection(object);
				break;
			case GameObject::Tag::poison:
				PoisonDetection(object);
				break;
			case GameObject::Tag::bomb:
				BombDetection(object);
				break;
			case GameObject::Tag::barrier:
				BarrierDetection(object);
				break;
			default:
				break;
			}
		}
	}

	PostcycleEX();
}

void Level::PostcycleEX()
{
}

void Level::GeneratePoison()
{
	for (int i = 0; i < poisonNum; i++) {
		poisons[i]->SetActive(true);
	}
}

void Level::FoodDetection(GameObject * collider)
{
	float distance = glm::distance(collider->transform.GetPositionVec(), head->transform.GetPositionVec());
	if (distance < 2) {
		food->Respawn();
		snake->OnEatFood();
	}
}

void Level::SnakeBodyDetection(GameObject * collider)
{
	float distance = glm::distance(collider->transform.GetPositionVec(), head->transform.GetPositionVec());
	if (distance < 1.5) {
		snake->Die();
	}
}

void Level::PoisonDetection(GameObject * collider)
{
	float distance = glm::distance(collider->transform.GetPositionVec(), head->transform.GetPositionVec());
	if (distance < 2) {
		((Bomb*)collider)->SetActive(false);
		snake->Decress();
	}
}

void Level::BombDetection(GameObject * collider)
{
	float distance = glm::distance(collider->transform.GetPositionVec(), head->transform.GetPositionVec());
	if (distance < 2) {
		int dl = (snake->GetLength() + 1) >> 1;
		while (dl--) {
			((Bomb*)collider)->Respawn();
			snake->Decress();
		}
	}
}

void Level::BarrierDetection(GameObject * collider)
{
	float distance = glm::distance(collider->transform.GetPositionVec(), head->transform.GetPositionVec());
	glm::vec3 s = collider->transform.GetScaleVec();
	float collideRadiu = (s.x + s.y + s.z) / 3;				//简化，假设所有碰撞体都接近球形且再模型空间中为单位尺寸
	if (distance < collideRadiu + 1) {
		snake->Die();
	}
}

void Level::ConfineDetection()
{
	float distance = glm::distance(
		snake->GetHead()->transform.GetPositionVec(),
		glm::vec3(0, 0, 0)
	);

	if (distance > (this->GetCurrentRadius() - 0.5f)) {
		snake->Die();
	}

}
