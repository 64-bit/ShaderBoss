#include "GlDebugWindow.h"
#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include <mathfu/glsl_mappings.h>

GLDebugWindow::GLDebugWindow()
{
	_timeOffset = glfwGetTime();

	glGenFramebuffers(1, &_windowFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _windowFramebuffer);

	glGenTextures(1, &_framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, _framebufferTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SIZE, SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _framebufferTexture, 0);

	auto vs = FileSystem::Open("SystemShaders/fullscreenquad.vert", true);
	auto fs = FileSystem::Open("SystemShaders/box.frag", true);

	_shaderProgram = ShaderProgram::CreateFromFiles(vs, fs);
}

void GLDebugWindow::OnFrame(float deltaT)
{
	ImVec2 dragDelta = ImGui::GetMouseDragDelta(0);

	glBindFramebuffer(GL_FRAMEBUFFER, _windowFramebuffer);
	glViewport(0, 0, SIZE, SIZE);

	_shaderProgram->Bind();

	auto loc = _shaderProgram->location("uTime");
	glUniform1f(loc, glfwGetTime() - _timeOffset);

	glDrawArrays(GL_TRIANGLES, 0, 6);



	//ImGui::SetNextWindowSize(ImVec2(512+8, 512+8));

	std::string title = std::string("GL WINDOW###") + std::to_string(_windowID);

	if (ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("THE FRAMES");
		ImVec2 size = ImVec2(512, 512);
		ImGui::Image((void*)_framebufferTexture, size);
	}
	ImGui::End();
}
