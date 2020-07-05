#include "AboutBox.h"
#include "imgui/imgui.h"

using namespace std;

void AboutBox::OnFrame(float deltaT)
{
	string title = string("About###") + to_string(_windowID);

	if (ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		ImGui::Text("TextureBoss");
		ImGui::Text("(C) Jonathan Linsner 2020");

		if (ImGui::Button("Close"))
		{
			Close();
		}
	}
	ImGui::End();
}
