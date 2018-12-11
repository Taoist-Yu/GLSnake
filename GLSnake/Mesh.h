#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<glad/glad.h>

#include<vector>

#include "Shader.h"

class Mesh
{
public:
	//����ṹ��
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	//���ʽṹ��
	struct Texture {
		enum TexType {
			diffuse,
			specular
		}type;
		GLuint id;
		std::string path;
	};

public:

	std::vector<Vertex> vertices;			//����
	std::vector<GLuint> indices;			//����
	std::vector<Texture> textures;			//����

	Mesh();
	Mesh(const Mesh&) = default;
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh();
	
	void Draw(Shader &shader);

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void SetupMesh();

};

