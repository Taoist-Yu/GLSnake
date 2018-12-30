#include "GameCanvas.h"
#include "Time.h"


GameCanvas::GameCanvas(Scene *scene)
	: Canvas(scene)
{
	this->returnButton = new ReturnButton(this);
	this->returnButton->SetActive(false);

	this->headline = new Sprite(this);
	this->headline->LoadTexture("UI/die.png");
	this->headline->scale = glm::vec2(1, 0.5);
	this->headline->position = glm::vec2(0, 0.5);
	this->headline->SetActive(false);

	this->processBar = new Sprite(this);
	this->processBar->LoadTexture("UI/processBar.png");
	this->processBar->position = glm::vec2(0, -0.975);
	this->processBar->scale = glm::vec2(1, 0.025);

	this->newLevel = new Sprite(this);
	this->newLevel->LoadTexture("UI/newLevel.png");
	this->newLevel->scale = glm::vec2(0.8, 0.4);
	this->newLevel->SetActive(false);

	this->finish= new Sprite(this);
	this->finish->LoadTexture("UI/finish.png");
	this->finish->scale = glm::vec2(0.8, 0.4);
	this->finish->SetActive(false);

}


GameCanvas::~GameCanvas()
{
	delete returnButton;
	delete headline;
	delete processBar;
	delete newLevel;
	delete finish;
}

void GameCanvas::PostUpdate()
{
	if (timeVal > 0) {
		timeVal -= Time.GetUnscaledDeltaTime();
	}
	else {
		finish->SetActive(false);
		newLevel->SetActive(false);
	}
}
