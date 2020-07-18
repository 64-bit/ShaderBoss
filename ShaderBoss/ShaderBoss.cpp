#include "ShaderBoss.h"
#include "imgui/imgui.h"
#include "UI/AboutBox.h"
#include "GraphicsResources/ShaderProgram.h"
#include "OSTemp/Files.h"
#include "glad/glad.h"
#include "UI/GlDebugWindow.h"
#include "UI/GlStats.h"
#include "OSTemp/OSFileSystemWrapper.h"
#include <iostream>
#include "GraphicsResources/ShaderDebugWindow.h"

static unsigned int VAO;


void TextureBoss::Init()
{
	_windowManager = new WindowManager();

	auto vs = FileSystem::Open("SystemShaders/fullscreenquad.vert", true);
	auto fs = FileSystem::Open("SystemShaders/grey.frag", true);

	_backgroundShader = ShaderProgram::CreateFromFiles(vs,fs);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	unsigned int VBO;




	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float* data = new float[6 * 3];

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 3, data, GL_STATIC_DRAW);

	auto debugWindow = new ShaderDebugWindow(_backgroundShader);
	_windowManager->OpenWindow(debugWindow);
}

void TextureBoss::MenuBar()
{
	static bool _hlsl = false;
	static bool _glsl = true;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "CTRL+Z"))
			{
				ShaderBoss::OSFileSystemWrapper::LoadFileDialoug("asdf");
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit"))
			{
				//TODO:Unsaved code
				//_shouldQuit = true; //TODO:
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Export"))
		{
			if (ImGui::MenuItem("GLSL", "", &_glsl))
			{
				_hlsl = false;
			}
			if (ImGui::MenuItem("HLSL", "", &_hlsl))
			{
				_glsl = false;
			}
			ImGui::Separator();
			ImGui::MenuItem("Export To Shader");
			ImGui::MenuItem("Export To PNG");
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("Shader Source"))
		{
			if (ImGui::MenuItem("Load All"))
			{
				auto str = ShaderBoss::OSFileSystemWrapper::LoadFileDialoug("asdf");
				std::cout << str.c_str();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Vertex Shader"))
			{

			}
			if (ImGui::MenuItem("Fragment Shader"))
			{

			}
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("Help"))
		{
			if(ImGui::MenuItem("About"))
			{
				//_aboutOpen = true;
				auto aboutWindow = new AboutBox();
				_windowManager->OpenWindow(aboutWindow);
			}

			if(ImGui::MenuItem("Gl Debug"))
			{
				auto debugWin = new GLDebugWindow();
				_windowManager->OpenWindow(debugWin);
			}

			if (ImGui::MenuItem("GL Stats"))
			{
				auto window = new GlStats();
				_windowManager->OpenWindow(window);
			}

			ImGui::MenuItem("ImGUI Debug", "", &_showDebugMenu);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void TextureBoss::OnFrameUI(float deltaT)
{
	MenuBar();

	//Node Editor ?

	//Sidebar ?

	//Do this last
	_windowManager->OnFrame(deltaT);

	if(_showDebugMenu)
	{
		ImGui::ShowDemoWindow();
	}

}

void TextureBoss::OnFrameBackground(float deltaT)
{
	DrawGLBackground(deltaT);
}


void TextureBoss::DrawGLBackground(float deltaT)
{
	glCullFace(GL_NONE);
	glDepthFunc(GL_ALWAYS);

	glVertexAttrib1f(0, 0);

	_backgroundShader->Bind();
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	
}
