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

// THIS SOURCE CODE STUFF WILL NOT STAY HERE BUT IS JUST HERE FOR NOW FOR TESTING.
// Vertex Shader source code.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.32f, 0.56f, 0.80f, 1.0f);\n"
"}\n\0";



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
	
	// Loads GLAD so that it configures opengl, and error checks.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initilize GLAD." << std::endl;
		return -1;
	}

	// Specifies the viewport of opengl in the window.
	glViewport(0, 0, monitorWidth, monitorHeight);



	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Vertices coordinates
	GLfloat vertices[] =
	{
		-1.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	// Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
	GLuint VAO, VBO, EBO;

	// Generate the VAO, VBO, and EBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	// Specifies the base color that the window is cleared/drawn-over with.
	glClearColor(0.08f, 0.14f, 0.20f, 1.0f);

	while (!glfwWindowShouldClose(window)) //Checks to see if you've "X-d out" the window.
	{
		// Clears the window with it's set basic clear color.
		glClear(GL_COLOR_BUFFER_BIT);



		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);



		//Swaps the windows back buffer canvas and it's front buffer canvas.
		glfwSwapBuffers(window);

		// Checks for window events.
		glfwPollEvents();
	}

	// Destroys the window, stops glfw stuff and ends the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
