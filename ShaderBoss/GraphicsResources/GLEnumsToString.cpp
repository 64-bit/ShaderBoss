#include "GLEnumsToString.h"
#include <cassert>



const char* GLEnumsToString::UniformTypeToString(GLenum enumerator)
{
	switch(enumerator)
	{
	case GL_FLOAT:
		return "Float";
	case GL_FLOAT_VEC2:
		return "Float Vector 2";
	case GL_FLOAT_VEC3:
		return "Float Vector 3";
	case GL_FLOAT_VEC4:
		return "Float Vector 4";

	case GL_INT:
		return "Int";
	case GL_INT_VEC2:
		return "Int Vector 2";
	case GL_INT_VEC3:
		return "Int Vector 3";
	case GL_INT_VEC4:
		return "Int Vector 4";

	case GL_FLOAT_MAT4:
		return "Float 4X4";

	default:
		assert(false);
	}
}