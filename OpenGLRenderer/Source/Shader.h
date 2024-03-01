#pragma once

#include "Defines.h"

#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind() const;

	void UploadUniformMat4(const char* name, const glm::mat4* matrix);

private:
	const char* ReadShaderSourceFromFile(const char* filePath);

private:
	u32 m_OpenGLID = NULL;
};
