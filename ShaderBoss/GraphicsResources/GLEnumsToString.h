#pragma once
#include <glad/glad.h>

class GLEnumsToString
{
public:
	GLEnumsToString() = delete;

	static const char* UniformTypeToString(GLenum enumerator);
};
