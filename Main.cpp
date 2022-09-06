/* Main.cpp file description:
* The core of the program, contains code relating to:
* - the window's functions
* 
* (Will later contain code also for the main game loop.)
*/

// These 3 includes are necessary for 3D rendering and general glad/glfw window functions.
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	// These 4 lines initialize glfw and instructs it on the version it's in, and that we won't be using/needing legacy/old features (instead just the core ones.)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Gets the primary monitor you will be using, and sets a variable to something that points to it in case you'd like to reference/use it more directly later.
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	// Gets the video-mode information of your primary monitor, including screen size.
	const GLFWvidmode * monitorVideoMode = glfwGetVideoMode(primaryMonitor);
	// Initializes monitorWidth and monitorHeight to the respective dimensions of your monitor.
	int monitorWidth = monitorVideoMode->width; int monitorHeight = monitorVideoMode->height;

	// Creates the window. If the 4th argument is filled in with primaryMonitor, having the program open will use the entire direct monitor itself, going into fullscreen mode.
	GLFWwindow* window = glfwCreateWindow(monitorWidth, monitorHeight, "Hatchetflash - Pre-Alpha", NULL, NULL); //(width, height, name, fullscreen monitor pointer, idk)
	// (An error-checking if statement:)
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	// Maximizes the window before beginning to use it.
	glfwMaximizeWindow(window);
	glfwMakeContextCurrent(window);
	
	// Loads GLAD so that it configures opengl.
	gladLoadGL();
	// Specifies the viewport of opengl in the window.
	glViewport(0, 0, monitorWidth, monitorHeight);

	// Specifies the base color that the window is cleared/drawn-over with.
	glClearColor(0.08f, 0.14f, 0.20f, 1.0f);
	// Clears the window with it's set basic clear color.
	glClear(GL_COLOR_BUFFER_BIT);
	// Swaps the windows back buffer canvas and it's front buffer canvas.
	glfwSwapBuffers(window);

	// Checks to see if you've "X-d out" the window.
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	// Destroys the window, stops glfw stuff and ends the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}