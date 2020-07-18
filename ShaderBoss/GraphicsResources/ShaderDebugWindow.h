#pragma once
#include "UI/Window.h"
#include "ShaderProgram.h"

class ShaderDebugWindow : public Window
{
public:
	ShaderDebugWindow(ShaderProgram* shader);

	void OnOpen() override;

	void OnFrame(float deltaT) override;

private:
	ShaderProgram* _targetProgram;
};
