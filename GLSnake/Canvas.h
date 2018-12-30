#pragma once
#include "Button.h"
#include <list>
#include <string>
#include <vector>

class Scene;

class Canvas
{
	friend Button::Button(Canvas* canvas);
	friend Sprite::Sprite(Canvas* canvas);
public:
	Canvas(Scene* scene);
	~Canvas();

	void Update();
	virtual void PostUpdate();

	void SetActive(bool active);
	bool GetActive();

protected:
	std::list<Button*> bottonList;
	std::list<Sprite*> spriteList;
	Scene* scene;

	bool isActive = true;
};

