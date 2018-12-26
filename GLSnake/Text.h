#pragma once
#include "Shader.h"
#include <string>
#include <map>

class Text
{
protected:
	static Shader* shader;

public:
	Text();
	~Text();

	void SetText(std::string text);
	std::string GetText();

	void Draw();

public:
	glm::vec2 position;
	glm::vec2 scale;

protected:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	std::map<char, GLuint> words;			//×Ö·ûÓëÌùÍ¼µÄÓ³Éä
	
	std::string text;
	
protected:
	void loadWords();
	void loadWord(char c, std::string name);
};

