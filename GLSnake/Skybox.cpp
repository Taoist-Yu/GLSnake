#include "Skybox.h"
#include<stb_image.h>
#include<iostream>

#include "Scene.h"

Skybox::Skybox()
{
}

Skybox::Skybox(std::string path)
{
	//load Shader
	shader = new Shader("skybox.vert", "skybox.frag");
	//load OpenGL object
	loadOpenglObject();
	//load sky box
	std::vector<std::string> faces
	{
		path + "/right.",
		path + "/left.",
		path + "/top.",
		path + "/bottom.",
		path + "/back.",
		path + "/front."
	};
	cubemapTexture = loadCubeMap(faces);
}


Skybox::~Skybox()
{
	//delete shader;
}

void Skybox::Draw(glm::mat4 view, glm::mat4 projection)
{
	view = glm::mat4(glm::mat3(view));
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);
	glDepthMask(GL_FALSE);
	shader->Enable();
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
 	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	shader->Disable();
	glDepthMask(GL_TRUE);
}

GLuint Skybox::loadCubeMap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glBindVertexArray(VAO);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	
	//���ͼƬ��ʽ
	std::vector<std::string> formats = { "jpg","tga","png" };
	std::string format;
	for (std::string _format : formats) {
		unsigned char *data = stbi_load((faces[0] + _format).c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			format = _format;
			break;
		}
	}

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load((faces[i] + format).c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return textureID;
}

void Skybox::loadOpenglObject()
{
	//vertices
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	//Set VAO,VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
