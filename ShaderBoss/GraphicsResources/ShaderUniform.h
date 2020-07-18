#pragma once
#include "GraphicsResources/GLTypes.h"
#include <string>
#include <vector>

class ShaderUniformBase
{
public:
	std::string Name;
	GLenum Type;
	int Index;

	static void ExtractAllUniformsToVector(std::vector<ShaderUniformBase*>& targetVector, GLuint shaderProgram);

	static ShaderUniformBase* FromGLShader(GLuint shaderProgram, int index);

	virtual void Bind() = 0;

protected:
	ShaderUniformBase(int index, char* name, GLenum type);
};

template <class T>
class ShaderUniform : public ShaderUniformBase
{
public:

	ShaderUniform(int index, char* name, GLenum type);

	void SetValue(const T& value);

	T GetValue();

	void Bind() override;

private:
	T _value;
	GLuint _uniformID;
};