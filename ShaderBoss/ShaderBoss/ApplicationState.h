#pragma once

namespace ShaderBoss
{
	class ProjectState;

	///This class represents the current state of the application, both the display scene and the current project
	///It deals with a lot of the rendering of the UI and tracking what state the UI is in.
	class ApplicationState
	{
		
	public:
		ApplicationState();

		~ApplicationState();

	private:
		ProjectState* _projectState;

	};
}