/* Main.cpp file description:
* The core of the program and the game, containing code relating to:
* - The program's main functions;
* - Code relating to the game's window;
* - and Rendering calls.
* 
* [Later on, this will also contain core loops of the game.]
*/

// These 3 includes are necessary for 3D rendering and general glad/glfw window functions:
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// These are for linear algebra for rendering.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Linux needs this, VS automatically adds it:
#include <cmath>

// Used for texture-related things:
#include <stb/stb_image.h>

// Rendering-based header files:
#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Texture-ish testing vertices.
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Front Lower left corner
	-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Front Upper left corner
	 0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Front Upper right corner
	 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	1.0f, 0.0f, // Front Lower right corner
	-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Back Lower left corner
	-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Back Upper left corner
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Back Upper right corner
	 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Back Lower right corner
};
// Texture-ish testing indices.
GLuint indices[] =
{
	0, 2, 1, // Upper triangle Front
	0, 3, 2, // Lower triangle Front
	3, 6, 2, // Upper triangle Right
	3, 7, 6, // Lower triangle Right
	7, 5, 6, // Upper triangle Back
	7, 4, 5, // Lower triangle Back
	4, 1, 5, // Upper triangle Left
	4, 0, 1, // Lower triangle Left
	1, 6, 5, // Back triangle Top
	1, 2, 6, // Front triangle Top
	4, 3, 0, // Front triangle Bottom
	4, 7, 3, // Back triangle Bottom
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

	// Enable depth testing so things are rendered in the correct order.
	glEnable(GL_DEPTH_TEST);

	// Gets the width and height of the window (instead of monitor) after it's created for the viewport, accounting for operating system specific weirdness like the window's taskbar.
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	// Specifies the viewport of opengl in the window.
	glViewport(0, 0, windowWidth, windowHeight);



	// Generates the Shader object using the shaders "defualt.vert" and "default.frag".
	Shader shaderProgram("default.vert", "default.frag");

	// Generates a Vertex Array Object and binds it.
	VAO VAO1;
	VAO1.Bind();

	// Generates a Vertex Buffer Object and links it to vertices.
	VBO VBO1(vertices, sizeof(vertices));
	// Generates an Element Buffer Object and links it to indices.
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO.
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbinds all to prevent accidentally modifying them later.
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// A texture for testing.
	stbi_set_flip_vertically_on_load(true);
	Texture testingTexture("Block_Textures/Album_2_Art.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	testingTexture.texUnit(shaderProgram, "tex0", 0);

	glm::mat4 transform = glm::mat4(1.0f);

	// Specifies the base color that the window is cleared/drawn-over with.
	glClearColor(0.02f, 0.15f, 0.17f, 1.0f);

	while (!glfwWindowShouldClose(window)) //Checks to see if you've "X-d out" the window.
	{
		// Clears the window with it's set basic clear color.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		transform = glm::rotate(transform, glm::radians(1.0f), glm::vec3(1.0, 0.0, 0.0));
		transform = glm::rotate(transform, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));
		transform = glm::rotate(transform, glm::radians(0.25f), glm::vec3(0.0, 0.0, 1.0));

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Assigns a value to the transform uniform; NOTE: Must always be done after activating the Shader Program
		GLuint transformID = glGetUniformLocation(shaderProgram.ID, "transform");
		glUniformMatrix4fv(transformID, 1, GL_FALSE, glm::value_ptr(transform));
		// Binds texture so that is appears in rendering
		testingTexture.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



		//Swaps the window's back buffer canvas and it's front buffer canvas.
		glfwSwapBuffers(window);

		// Checks for window events.
		glfwPollEvents();
	}

	// Cleanly deletes all of the created rendering-based objects.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	testingTexture.Delete();
	shaderProgram.Delete();
	// Destroys the window, stops glfw stuff and ends the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
