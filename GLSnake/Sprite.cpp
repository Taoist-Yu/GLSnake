#include "Sprite.h"
#include "Debug.h"
#include <stb_image.h>
#include <iostream>
#include "Canvas.h"

Shader* Sprite::shader = NULL;

Sprite::Sprite()
{
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	color = glm::vec4(1, 1, 1, 1);

	//精灵全为矩形，固定的顶点数据 
	GLfloat vertices[] = {
		1.0f, 1.0f, 0.0f,		1,1,
		1.0f, -1.0f, 0.0f,		1,0,
		-1.0f, -1.0f, 0.0f,		0,0,
		-1.0f, 1.0f, 0.0f,		0,1,
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLuint), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLuint), (void*)(3 * sizeof(float)));		//pos == texcoords
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Sprite::Sprite(Canvas * canvas)
	:Sprite()
{
	this->canvas = canvas;
	canvas->spriteList.push_back(this);
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Sprite::Draw()
{
	if (shader == NULL) {
		shader = new Shader("sprite.vert", "sprite.frag");
	}
	if (textureID == 0)
		return;

	shader->SetVec3("position", glm::vec3(position, 0.0f));
	shader->SetVec3("scale", glm::vec3(scale, 1.0f));
	shader->SetVec4("color", color);

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

void Sprite::LoadTexture(std::string path)
{
	if (textureID != 0) {
		glDeleteTextures(1, &textureID);
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if(nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Debug::Error("Failed to load image:" + path);
	}
	stbi_set_flip_vertically_on_load(false);
	stbi_image_free(data);
}

void Sprite::SetActive(bool active)
{
	this->isActive = active;
}

bool Sprite::GetActive()
{
	return this->isActive;
}
