#include "Text.h"
#include "Debug.h"

#include <stb_image.h>
#include<iostream>

Shader* Text::shader;

Text::Text()
{
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	//精灵全为矩形，固定的顶点数据 
	GLfloat vertices[] = {
		0.05f, 0.05f, 0.0f,
		0.05f, -0.05f, 0.0f,
		-0.05f, -0.05f, 0.0f,
		-0.05f, 0.05f, 0.0f
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLuint), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLuint), (void*)0);		//pos == texcoords
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	loadWords();
}

Text::~Text()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Text::SetText(std::string text)
{
	this->text = text;
}

std::string Text::GetText()
{
	return text;
}

void Text::Draw()
{

	if (shader == NULL) {
		shader = new Shader("Text.vert", "Text.frag");
	}
	shader->SetVec3("scale", glm::vec3(scale, 1.0f));

	for (int i = 0; i < text.length();i++) {
		GLuint textureID = words[text[i]];
		shader->SetVec3("position", glm::vec3(position + glm::vec2(i * scale.x / 10, 0), 0.0f));
		shader->Enable();
		glDepthMask(GL_FALSE);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDepthMask(GL_TRUE);
		shader->Disable();
	}

}

void Text::loadWords()
{
	loadWord('1', "1.jpg");
	loadWord('2', "2.jpg");
	loadWord('3', "3.jpg");
	loadWord('4', "4.jpg");
	loadWord('5', "5.jpg");
	loadWord('6', "6.jpg");
	loadWord('7', "7.jpg");
	loadWord('8', "8.jpg");
	loadWord('9', "9.jpg");
	loadWord('0', "0.jpg");
	loadWord(':', "colon.jpg");
}

void Text::loadWord(char c, std::string name)
{
	name = "font/" + name;
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Debug::Error("Failed to load image:" + name);
	}
	stbi_image_free(data);
	words[c] = textureID;
}
