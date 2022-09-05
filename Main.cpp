#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode * monitorVideoMode = glfwGetVideoMode(primaryMonitor);
	int monitorWidth = monitorVideoMode->width; int monitorHeight = monitorVideoMode->height;

	GLFWwindow* window = glfwCreateWindow(monitorWidth, monitorHeight, "Hatchetflash - Pre-Alpha", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMaximizeWindow(window);
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	glViewport(0, 0, monitorWidth, monitorHeight); //NOT SURE IF WIDTH AND HEIGHT NEED TO BE SWAPPED.

	glClearColor(0.08f, 0.14f, 0.20f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}