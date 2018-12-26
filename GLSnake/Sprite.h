#pragma once
#include "Shader.h"
#include <string>

class Sprite
{
protected:
	static Shader* shader;

public:
	Sprite();
	~Sprite();

	void Draw();
	void LoadTexture(std::string path);

public:
	glm::vec2 position;
	glm::vec2 scale;

protected:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint textureID;

};

