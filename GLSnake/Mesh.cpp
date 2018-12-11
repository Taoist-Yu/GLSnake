#include "Mesh.h"

#include<iostream>

Mesh::Mesh()
{
	this->vertices.push_back(
		Vertex{
			glm::vec3(-0.5, 0.5, 0),
			glm::vec3(1, 1, 1)
		}
	);
	this->vertices.push_back(
		Vertex{
			glm::vec3(0.5, 0.5, 0),
			glm::vec3(1, 0, 0)
		}
	);
	this->vertices.push_back(
		Vertex{
			glm::vec3(-0.5, -0.5, 0),
			glm::vec3(0, 1, 0)
		}
	);
	this->vertices.push_back(
		Vertex{
			glm::vec3(0.5, -0.5, 0),
			glm::vec3(0, 0, 1)
		}
	);

	int _indices[] = {
		0,1,2,
		1,2,3
	};
	this->indices = std::vector<GLuint>(_indices, _indices + 6);

	SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->SetupMesh();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Draw(Shader & shader)
{
	GLuint diffuseNr = 0;
	GLuint specularNr = 0;
	//设置Texture，设置采样器uniform
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		GLuint number;
		Texture::TexType type = textures[i].type;
		if (type == Texture::diffuse)
		{
			number = diffuseNr++;
			shader.SetTextureUnit("texture_diffuse" + number, i);
		}
		else if (type == Texture::specular)
		{
			number = specularNr++;
			shader.SetTextureUnit("texture_specular" + number, i);
		}
	}
	//绘制三角形
	shader.Enable();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	shader.Disable();
	//重置TextureBuffer和shader中的uniform变量
	diffuseNr = specularNr = 0;
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
		std::string number;
		Texture::TexType type = textures[i].type;
		if (type == Texture::diffuse)
		{
			number = std::to_string(diffuseNr++);
			shader.SetTextureUnit("texture_diffuse" + number, 0);
		}
		else if (type == Texture::specular)
		{
			number = std::to_string(specularNr++);
			shader.SetTextureUnit("texture_specular" + number, 0);
		}
	}
	//将当前激活的纹理单元重置为默认值
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
