#include "Defines.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "[GLFW][ERROR]: %s\n", description);
}

#if 0
int main(void)
{
	FILE* file = fopen("Resources/Textures/Default.png", "rb");
	if (!file)
		return -1;

	fseek(file, 0, SEEK_END);
	u64 length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buf = new char[length + 1];

	if (fread(buf, sizeof(char), length, file) != length)
		return -1;

	buf[length] = '\0';

	for (u64 i = 0; i < length; i++)
		printf("%c", buf[i]);

	fclose(file);
}
#else
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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Renderer", NULL, NULL);
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

	VertexArray vao;
	vao.Bind();

	f32 vertices[] = {
		 0.0f,  0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f
	};
	
	VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices));
	vbo.Bind();

	// TODO: Move to VertexBuffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)NULL);

	u32 indices[] = {
		0, 1, 2
	};
	u32 indicesCount = sizeof(indices) / sizeof(indices[0]);

	IndexBuffer ibo = IndexBuffer(indices, indicesCount);
	ibo.Bind();

	Shader shader = Shader("Resources/Shaders/vertex_shader.txt", "Resources/Shaders/fragment_shader.txt");
	shader.Bind();

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

		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
#endif