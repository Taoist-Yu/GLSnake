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
#include "Mesh.h"

class Model
{
private:
	std::vector<Mesh::Texture> textures_loaded;

public:
	/*  ����   */
	Model();
	Model(const char *path);
	~Model();
	void Draw(Shader& shader);
private:
	/*  ģ������  */
	std::vector<Mesh*> meshes;
	std::string directory;
	/*  ����   */
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		Mesh::Texture::TexType typeName);
	//����һ������,������ID
	GLuint TextureFromFile(const char *path, const std::string &directory);
};