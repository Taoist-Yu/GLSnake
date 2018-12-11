#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint id;
	Shader() = default;
	Shader(const Shader&) = default;
	Shader(const char* vShaderFile, const char* fShaderFile);
	void Enable() const;
	void Disable() const;
	virtual ~Shader();

//Uniform
public:
	void SetInt(const std::string name, int value) const;
	void SetBool(const std::string name, bool value) const;
	void SetFloat(const std::string name, float value) const;
	void SetTextureUnit(const std::string name, int value) const;
	void SetMat4(const std::string& name,const glm::mat4 &value) const;

private:
	enum ErrorType {
		CompileError,
		LinkError
	};

	void CreateShaderProgram(const char* vShaderFile, const char* fShaderFile);
	std::string ReadFile(const char* FileName);
	void ErrorCheck(GLuint shader, ErrorType errorType);

};

