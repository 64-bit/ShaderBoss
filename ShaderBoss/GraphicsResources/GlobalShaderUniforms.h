#pragma once
#include <mathfu/glsl_mappings.h>
#include "glad/glad.h"

class GlobalShaderUniforms
{

public:
	mathfu::vec3 CameraPosition;
	mathfu::vec3 CameraForward;

	mathfu::mat4 ViewMatrix;
	mathfu::mat4 ProjectionMatrix;

	void SetTime(float time, float deltaTime);

	void SetMatricies(const mathfu::mat4& viewMatrix, const mathfu::mat4& projectionMatrix);

	void SetCamera(const mathfu::vec3& cameraPosition, const mathfu::vec3& cameraForward);

private:
	GLuint _uniformBufferObject;

};

class GlobalShaderUniformsBuffer
{
public:
	float Time;
	float DeltaTime;
};