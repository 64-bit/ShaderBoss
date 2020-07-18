#include "ShaderUniform.h"
#include <glad/glad.h>
#include <iostream>
#include <mathfu/glsl_mappings.h>

using namespace std;
using namespace mathfu;

ShaderUniformBase::ShaderUniformBase(int index, char* name, GLenum type)
{
	Index = index;
	Name = string(name);
	Type = type;
}


void ShaderUniformBase::ExtractAllUniformsToVector(std::vector<ShaderUniformBase*>& targetVector, GLuint shaderProgram)
{
	int uniformCount;
	glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniformCount);
	printf("Active Uniforms: %d\n", uniformCount);

	for(int i = 0; i < uniformCount;i++)
	{
		const auto uniform = FromGLShader(shaderProgram, i);
		targetVector.push_back(uniform);
	}
}

template<class T>
ShaderUniform<T>::ShaderUniform(int index, char* name, GLenum type) : ShaderUniformBase(index,name,type)
{
	
}


#define UNIFORM_TYPE(GL_TYPE,CPP_TYPE)  case GL_TYPE:return new ShaderUniform<CPP_TYPE>(index, name, type);break;

ShaderUniformBase* ShaderUniformBase::FromGLShader(GLuint shaderProgram, int index)
{
	int size;
	GLenum type;

	const size_t bufferSize = 128;
	char name[bufferSize];
	int length;

	glGetActiveUniform(shaderProgram, (GLuint)index, bufferSize, &length, &size, &type, name);

	switch(type)
	{
		UNIFORM_TYPE(GL_FLOAT, float);
		UNIFORM_TYPE(GL_FLOAT_VEC2, vec2);
		UNIFORM_TYPE(GL_FLOAT_VEC3, vec3);
		UNIFORM_TYPE(GL_FLOAT_VEC4, vec4);

		UNIFORM_TYPE(GL_INT, int);
		UNIFORM_TYPE(GL_INT_VEC2, vec2i);
		UNIFORM_TYPE(GL_INT_VEC3, vec3i);
		UNIFORM_TYPE(GL_INT_VEC4, vec4i);

		UNIFORM_TYPE(GL_FLOAT_MAT4, mat4);

	default:
		//THROW

		break;
	}
}

//Explicit specs
template<>
void ShaderUniform<float>::Bind()
{
	glUniform1f(Index, _value);
}

template<>
void ShaderUniform<vec2>::Bind()
{
	glUniform2fv(Index,2, reinterpret_cast<float*>(&_value));
}

template<>
void ShaderUniform<vec3>::Bind()
{
	glUniform3fv(Index, 3, reinterpret_cast<float*>(&_value));
}

template<>
void ShaderUniform<vec4>::Bind()
{
	glUniform4fv(Index, 4, reinterpret_cast<float*>(&_value));
}

template<>
void ShaderUniform<int>::Bind()
{
	glUniform1i(Index, _value);
}

template<>
void ShaderUniform<vec2i>::Bind()
{
	glUniform2iv(Index, 2, reinterpret_cast<int*>(&_value));
}

template<>
void ShaderUniform<vec3i>::Bind()
{
	glUniform3iv(Index, 3, reinterpret_cast<int*>(&_value));
}

template<>
void ShaderUniform<vec4i>::Bind()
{
	glUniform4iv(Index, 4, reinterpret_cast<int*>(&_value));
}

template<>
void ShaderUniform<mat4>::Bind()
{
	glUniformMatrix4fv(Index, 16,false, reinterpret_cast<float*>(&_value));
}

template<class T>
void ShaderUniform<T>::Bind()
{
	assert(false);
}
