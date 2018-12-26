#pragma once
#include "Scene.h"

#include "Snake.h"
#include "Food.h"
#include "Confine.h"
#include "Poison.h"
#include "Bomb.h"

class Level :
	public Scene
{
public:
	//�������һ������������λ��
	static glm::vec3 ObjectRespawnPosition(Scene* scene);

public:
	enum Difficulty {
		easy,
		normal,
		hard,
		huaji
	}difficulty;

public:
	Level();
	virtual ~Level();

	void GameStart();
	void GameOver();

	float GetCurrentRadius();

protected:
	void Postcycle();
	virtual void PostcycleEX();						//�ض��ؿ�����ָ��������

	void GeneratePoison();

	void FoodDetection(GameObject* collider);
	void SnakeBodyDetection(GameObject* collider);
	void PoisonDetection(GameObject* collider);
	void BombDetection(GameObject* collider);
	void BarrierDetection(GameObject* collider);
	void ConfineDetection();

protected:
	Confine* confine;
	Snake* snake;
	Food* food;

	int poisonNum;
	float poisonTimeVal = 0;
	Poison* poisons[100];

	int bombNum;
	Bomb* bombs[50];

	const SnakeNode* head;
	
};

