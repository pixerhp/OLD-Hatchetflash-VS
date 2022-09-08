/* Main.cpp file description:
* The core of the program and the game, containing code relating to:
* - The program's main functions;
* - Code relating to the game's window;
* - and Rendering calls.
* 
* [Later on, this will also contain core loops of the game.]
*/

// These 3 includes are necessary for 3D rendering and general glad/glfw window functions.
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Linux needs this, VS automatically adds it.
#include <cmath>

// Rendering header files
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Triangle-ish testing vertices.
GLfloat vertices[] =
{
	-1.0f, -1.73f * float(sqrt(3)) / 3, 0.0f, //Lower left corner vertex.
	0.0f, 0.0f * float(sqrt(3)) / 3, 0.0f, //Lower right corner vertex.
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //Upper corner vertex.
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner left vertex.
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner right vertex.
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //Inner down vertex.
};
// Triangle-ish testing indices.
GLuint indices[] =
{
	0, 3, 5, //Lower left triangle.
	3, 2, 4, //Lower right triangle.
	5, 4, 1 //Upper equilateral triangle.
};



// Jcodefox's function to resize the canvas when you resize the window.
void framebuffer_size_callback(GLFWwindow* window, int w, int h){
	glViewport(0, 0, w, h);
}



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
	GLFWwindow* window = glfwCreateWindow(monitorWidth, monitorHeight, "Hatchetflash - Pre-Alpha", NULL, NULL); //(width, height, name, fullscreen monitor pointer, not-important)
	// (An error-checking if statement:)
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	// Maximizes the window before beginning to use it, and then prepares a callback for resizing the canvas when you resize the window.
	glfwMaximizeWindow(window);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// Loads GLAD so that it configures opengl, and error checks.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initilize GLAD." << std::endl;
		return -1;
	}

	// Specifies the viewport of opengl in the window.
	glViewport(0, 0, monitorWidth, monitorHeight);



	// Generates the Shader object using the shaders "defualt.vert" and "default.frag".
	Shader shaderProgram("default.vert", "default.frag");

	// Generates a Vertex Array Object and binds it.
	VAO VAO1;
	VAO1.Bind();

	// Generates a Vertex Buffer Object and links it to the triangle-testing vertices.
	VBO VBO1(vertices, sizeof(vertices));
	// Generates an Element Buffer Object and links it to the triangle-testing vertices.
	EBO EBO1(indices, sizeof(indices));

	// Links the VBO to the VAO.
	VAO1.LinkVBO(VBO1, 0);
	// Unbinds these to prevent accidentally modifying them later.
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	// Specifies the base color that the window is cleared/drawn-over with.
	glClearColor(0.08f, 0.14f, 0.20f, 1.0f);

	while (!glfwWindowShouldClose(window)) //Checks to see if you've "X-d out" the window.
	{
		// Clears the window with it's set basic clear color.
		glClear(GL_COLOR_BUFFER_BIT);



		// Tells OpenGL which Shader Program we want to use, and binds the VAO so that OpenGL knows to use it.
		shaderProgram.Activate();
		VAO1.Bind();
		// Draws the triangle-testing vertices.
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //(primitives, number of indices, datatype of indices, index of indices)



		//Swaps the window's back buffer canvas and it's front buffer canvas.
		glfwSwapBuffers(window);

		// Checks for window events.
		glfwPollEvents();
	}

	// Cleanly deletes all of the created rendering-based objects.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Destroys the window, stops glfw stuff and ends the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
