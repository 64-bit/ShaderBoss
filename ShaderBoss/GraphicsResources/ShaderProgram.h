#pragma once
#include "OSTemp/Files.h"
#include "GraphicsResources/GLTypes.h"
#include <vector>

class ShaderUniformBase;

//Represents a fully linked vertex and fragment shader
class ShaderProgram
{
public:

	static ShaderProgram* CreateFromFiles(File& vertexShader, File& fragmentShader);

	static ShaderProgram* CreateFromStrings(const char* vertexShader, const char* fragmentShader);

	int location(const char* loc);

	void Bind();

	const std::vector<ShaderUniformBase*>* GetUniforms();

private:

	std::vector<ShaderUniformBase*> _shaderUniforms;

	ShaderProgram(const char* vertexShader, const char* fragmentShader);

	void BindAttributes();

	void BindUniforms();

	GLuint _vertexShader;
	GLuint _fragmentShader;
	GLuint _shaderProgram;

	bool _isCompiledOk;

	
};