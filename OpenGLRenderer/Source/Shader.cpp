#include "Shader.h"

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// TODO: Cleanup

	// ========== Vertex Shader ==========

	const char* vertexSrc = ReadShaderSourceFromFile(vertexPath);

	i32 isCompiled = NULL;

	i32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);

	delete[] vertexSrc;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		i32 messageLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &messageLength);

		char* message = new char[messageLength];
		glGetShaderInfoLog(vertexShader, messageLength, &messageLength, message);

		fprintf(stderr, "[ERROR]: Vertex shader compilation failed: %s\n", message);

		glDeleteShader(vertexShader);
		delete[] message;
		return;
	}

	// ========== Fragment Shader ==========

	const char* fragmentSrc = ReadShaderSourceFromFile(fragmentPath);

	i32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);

	delete[] fragmentSrc;

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		i32 messageLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &messageLength);

		char* message = new char[messageLength];
		glGetShaderInfoLog(fragmentShader, messageLength, &messageLength, message);

		fprintf(stderr, "[ERROR]: Fragment shader compilation failed: %s\n", message);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		delete[] message;
		return;
	}

	// ========== Shader Program ==========

	m_OpenGLID = glCreateProgram();
	glAttachShader(m_OpenGLID, vertexShader);
	glAttachShader(m_OpenGLID, fragmentShader);
	glLinkProgram(m_OpenGLID);

	i32 isLinked = NULL;
	glGetProgramiv(m_OpenGLID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		i32 messageLength = 0;
		glGetProgramiv(m_OpenGLID, GL_INFO_LOG_LENGTH, &messageLength);

		char* message = new char[messageLength];
		glGetProgramInfoLog(m_OpenGLID, messageLength, &messageLength, message);

		fprintf(stderr, "[ERROR]: Shader program linking failed: %s\n", message);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(m_OpenGLID);
		delete[] message;
		return;
	}

	glDetachShader(m_OpenGLID, vertexShader);
	glDetachShader(m_OpenGLID, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_OpenGLID);
}

void Shader::Bind() const
{
	glUseProgram(m_OpenGLID);
}

void Shader::UploadUniformMat4(const char* name, const glm::mat4* matrix)
{
	i32 location = glGetUniformLocation(m_OpenGLID, name);
	if (location == -1)
	{
		fprintf(stderr, "[ERROR]: Cannot find location for uniform name: %s", name);
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*matrix));
}

// IT IS THE USERS RESPONSABILITY TO FREE THE MEMORY RETURNED BY THIS FUNCTION
const char* Shader::ReadShaderSourceFromFile(const char* filePath)
{
	FILE* file = fopen(filePath, "rb");  // TODO: Find out why we need to read the file in binary mode
	if (!file)
	{
		fprintf(stderr, "[ERROR]: Cannot open file: %s", filePath);
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	u32 length = ftell(file);
	fseek(file, 0, SEEK_SET);  // NOTE: Can also use 'rewind(file);'

	char* contents = new char[length + 1];

	if (fread(contents, sizeof(char), length, file) != length)
	{
		fprintf(stderr, "[ERROR]: Cannot read from file: %s", filePath);
		fclose(file);
		delete[] contents;
		return nullptr;
	}

	fclose(file);

	contents[length] = '\0';  // TODO: Find out why we need to add the null terminator to the end of the string

	return contents;
}