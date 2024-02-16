#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "[ERROR][GLFW]: %s\n", description);
}

int main(void)
{
	glfwSetErrorCallback(GLFWErrorCallback);

	if (!glfwInit())
	{
		fprintf(stderr, "[ERROR]: Failed to initialize GLFW");
		return -1;
	}

	// TODO: Set window hints
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "[ERROR]: Failed to create window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "[ERROR]: Failed to initialize GLEW");
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}