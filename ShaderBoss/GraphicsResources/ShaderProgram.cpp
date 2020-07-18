#include "ShaderProgram.h"
#include <glad/glad.h>
#include <cstring>
#include <iostream>
#include "ShaderUniform.h"

ShaderProgram * ShaderProgram::CreateFromFiles(File & vertexShader, File & fragmentShader)
{
	return CreateFromStrings(vertexShader.Data, fragmentShader.Data);
}

ShaderProgram * ShaderProgram::CreateFromStrings(const char * vertexShader, const char * fragmentShader)
{
	return new ShaderProgram(vertexShader, fragmentShader);
}

int ShaderProgram::location(const char * loc)
{
	return glGetUniformLocation(_shaderProgram, loc);
}

void ShaderProgram::Bind()
{
	glUseProgram(_shaderProgram);
	BindUniforms();
}

const std::vector<ShaderUniformBase*>* ShaderProgram::GetUniforms()
{
	return &_shaderUniforms;
}

void ShaderProgram::BindUniforms()
{
	for(auto uniform : _shaderUniforms)
	{
		uniform->Bind();
	}
}


ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragmentShader)
{
	int  success;

	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShader, 1, &vertexShader, nullptr);
	glCompileShader(_vertexShader);

	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		std::cout << "Failed to compile vertex shader\r\n";
	}


	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShader, 1, &fragmentShader, nullptr);
	glCompileShader(_fragmentShader);

	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		std::cout << "Failed to compile fragment shader\r\n";

		GLint logSize = 0;
		GLsizei outsize;
		glGetShaderiv(_fragmentShader, GL_INFO_LOG_LENGTH, &logSize);
		char* msg = new char[logSize];
		glGetShaderInfoLog(_fragmentShader, logSize, &outsize, msg);

		std::cout << msg;
	}

	_shaderProgram = glCreateProgram();

	BindAttributes();

	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);

	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if(!success)
	{
		std::cout << "failed to link shader\n";
	}

	ShaderUniformBase::ExtractAllUniformsToVector(_shaderUniforms, _shaderProgram);


	for(int i = 0; i < _shaderUniforms.size();i++)
	{
		printf("Uniform #%d -- %s\n", _shaderUniforms[i]->Index, _shaderUniforms[i]->Name.c_str());
	}

	std::cout << " Shader finished\n";
}

void ShaderProgram::BindAttributes()
{
	glBindAttribLocation(_shaderProgram, 0, "a_pos");
	glBindAttribLocation(_shaderProgram, 1, "a_uv");
}