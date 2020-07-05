#pragma once

#include "Window.h"
#include "glad/glad.h"
#include "GraphicsResources/ShaderProgram.h"

class GLDebugWindow : public Window
{
	int SIZE = 1024;

public:

	GLDebugWindow();

	void OnFrame(float deltaT) override;


private:
	float _timeOffset;
	GLuint _windowFramebuffer;
	GLuint _framebufferTexture;

	ShaderProgram* _shaderProgram;
};
