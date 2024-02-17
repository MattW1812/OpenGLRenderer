#include "Defines.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "[GLFW][ERROR]: %s\n", description);
}

int main(void)
{
	glfwSetErrorCallback(GLFWErrorCallback);

	if (!glfwInit())
	{
		fprintf(stderr, "[ERROR]: Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const u32 width = 1280;
	const u32 height = 720;
	GLFWwindow* window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "[ERROR]: Failed to create window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "[ERROR]: Failed to initialize GLEW\n");
		return -1;
	}

	printf("[OPENGL][INFO]: GL_VERSION: %s\n", glGetString(GL_VERSION));
	printf("[OPENGL][INFO]: GL_VENDOR: %s\n", glGetString(GL_VENDOR));
	printf("[OPENGL][INFO]: GL_RENDERER: %s\n", glGetString(GL_RENDERER));
	printf("[OPENGL][INFO]: GL_SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//printf(stdout, "[INFO]: GL_EXTENSIONS: %u", glGetString(GL_EXTENSIONS));

	glViewport(0, 0, width, height);

	u32 vao;
	glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	f32 vertices[] = {
		 0.0f,  0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f
	};
	
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)NULL);

	u32 indices[] = {
		0, 1, 2
	};
	u32 indicesCount = sizeof(indices) / sizeof(indices[0]);

	u32 ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	i32 isCompiled = NULL;

	const char* vertexShaderSrc = R"(
		#version 330 core

		layout (location = 0) in vec3 a_Position;

		void main()
		{
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

	i32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		i32 messageLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &messageLength);

		char* message = new char[messageLength];
		glGetShaderInfoLog(vertexShader, messageLength, &messageLength, message);

		fprintf(stderr, "[ERROR]: Vertex shader compilation failed: %s\n", message);

		delete[] message;
		glDeleteShader(vertexShader);
		return -1;
	}

	const char* fragmentShaderSrc = R"(
			#version 330 core

			out vec4 o_FragColor;

			void main()
			{
				o_FragColor = vec4(1.0);
			}
	)";

	i32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		i32 messageLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &messageLength);

		char* message = new char[messageLength];
		glGetShaderInfoLog(fragmentShader, messageLength, &messageLength, message);

		fprintf(stderr, "[ERROR]: Vertex shader compilation failed: %s\n", message);

		delete[] message;
		glDeleteShader(fragmentShader);
		return -1;
	}

	u32 shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	i32 isLinked = NULL;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		i32 messageLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &messageLength);

		char* message = new char[messageLength];
		glGetProgramInfoLog(shaderProgram, messageLength, &messageLength, message);

		fprintf(stderr, "[ERROR]: Shader program linking failed: %s\n", message);

		delete[] message;
		glDeleteProgram(shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return -1;
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);

	u32 error = glGetError();
	if (error)
	{
		// TODO: Switch on error code
		fprintf(stderr, "[OPENGL][ERROR]: OpenGL failed with error code: %u\n", error);
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}