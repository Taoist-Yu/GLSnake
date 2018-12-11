#include "Shader.h"

#include<string>
#include<sstream>
#include<iostream>
#include<fstream>

#include"Debug.h"
using namespace std;

Shader::Shader(const char * vShaderFile, const char * fShaderFile)
{
	CreateShaderProgram(vShaderFile, fShaderFile);
}

void Shader::Enable() const
{
	glUseProgram(id);
}

void Shader::Disable() const
{
	glUseProgram(0);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::SetInt(const std::string name, int value) const
{
	this->Enable();
	GLuint location = glGetUniformLocation(id, name.c_str());
	this->Disable();
}

void Shader::SetBool(const std::string name, bool value) const
{
	this->Enable();
	glUniform1i(glGetAttribLocation(id,name.c_str()), (int)value);
	this->Disable();
}

void Shader::SetFloat(const std::string name, float value) const
{
	this->Enable();
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	this->Disable();
}

void Shader::SetTextureUnit(const std::string name, int value) const
{
	this->Enable();
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	this->Disable();
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const
{
	this->Enable();
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	this->Disable();
}

void Shader::CreateShaderProgram(const char * vShaderFile, const char * fShaderFile)
{
	string vShaderCodeString = ReadFile(vShaderFile);
	string fShaderCodeString = ReadFile(fShaderFile);

	const char* vShaderCode = vShaderCodeString.c_str();
	const char* fShaderCode = fShaderCodeString.c_str();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertShader, 1, &vShaderCode, NULL);
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	glCompileShader(vertShader);
	glCompileShader(fragShader);
	id = glCreateProgram();
	glAttachShader(id, vertShader);
	glAttachShader(id, fragShader);
	glLinkProgram(id);
	this->ErrorCheck(vertShader, CompileError);
	this->ErrorCheck(fragShader, CompileError);
	this->ErrorCheck(id, LinkError);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

std::string Shader::ReadFile(const char * FileName)
{
	ifstream fin(FileName);
	stringstream sourceStream;
	string source;
	sourceStream << fin.rdbuf();
	source = sourceStream.str();
	fin.close();
	return string(source);
}

void Shader::ErrorCheck(GLuint shader,ErrorType errorType)
{
	int success;
	char infoLog[1024];
	if (errorType == CompileError)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			Debug::Error(
				"ERROR::SHADER_COMPILATION_ERROR: " +
				string(infoLog) +
				"\n -- --------------------------------------------------- -- "
			);
		}
	}
	else if(errorType == LinkError)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			Debug::Error(
				"ERROR::PROGRAM_LINKING_ERROR: " +
				string(infoLog) +
				"\n -- --------------------------------------------------- -- "
			);
		}
	}
}
