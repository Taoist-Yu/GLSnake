#pragma once
#include "Shader.h"
#include <string>

class Canvas;

class Sprite
{
protected:
	static Shader* shader;

public:
	Sprite();
	Sprite(Canvas* canvas);
	~Sprite();

	void Draw();
	void LoadTexture(std::string path);

	void SetActive(bool active);
	bool GetActive();

public:
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec4 color;

protected:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint textureID;

	bool isActive = true;
	Canvas* canvas;

};

