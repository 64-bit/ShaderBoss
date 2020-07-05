#include "GlStats.h"
#include "imgui/imgui.h"
#include "glad/glad.h"
#include <string>

using namespace std;


#define glDebugText(ENUM) {int outValue; glGetIntegerv(ENUM, &outValue); 		ImGui::Text((string(#ENUM) + string(": ") + to_string(outValue)).c_str());}

void GlStats::OnFrame(float deltaT)
{
	bool open = true;
	if(ImGui::Begin("OpenGL Info", &open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		/*int outValue;

		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &outValue);
		ImGui::Text((string("GL_MAX_UNIFORM_BUFFER_BINDINGS:") + to_string(outValue)).c_str());*/

		glDebugText(GL_MAX_UNIFORM_BUFFER_BINDINGS);
		glDebugText(GL_MAX_UNIFORM_BLOCK_SIZE);
		glDebugText(GL_MAX_VERTEX_UNIFORM_BLOCKS);
		glDebugText(GL_MAX_FRAGMENT_UNIFORM_BLOCKS);
		glDebugText(GL_MAX_GEOMETRY_UNIFORM_BLOCKS);

	}
	ImGui::End();

	if(!open)
	{
		Close();
	}
}
