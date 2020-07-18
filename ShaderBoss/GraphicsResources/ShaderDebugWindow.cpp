#include "ShaderDebugWindow.h"
#include "imgui/imgui_impl_opengl3.h"
#include "GraphicsResources/ShaderUniform.h"
#include "GLEnumsToString.h"

ShaderDebugWindow::ShaderDebugWindow(ShaderProgram* shader)
{
	_targetProgram = shader;
}

void ShaderDebugWindow::OnOpen()
{
	Window::OnOpen();
}

void ShaderDebugWindow::OnFrame(float deltaT)
{

	std::string title = std::string("ShaderStats WINDOW###") + std::to_string(_windowID);

	if (ImGui::Begin(title.c_str(), nullptr, 0))
	{
		ImGui::Text("Shader Debug");

		char buffer[512];

		auto uniforms = _targetProgram->GetUniforms();

		snprintf(buffer, 512, "Shader Name:%s", "TEMP_SHADER_NAME_ADD_FEATURE");
		ImGui::Text(buffer);

		snprintf(buffer, 512, "Total Uniforms:%d", uniforms->size());
		ImGui::Text(buffer);

		for(auto& uniform : *uniforms)
		{
			snprintf(buffer, 512, "%s:%s", uniform->Name.c_str(), GLEnumsToString::UniformTypeToString(uniform->Type));
			ImGui::Text(buffer);
		}
	}
	ImGui::End();
}