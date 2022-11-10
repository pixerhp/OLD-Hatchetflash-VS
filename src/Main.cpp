/* =-= =-= =-= =-= =-= =-= =-= J.M.J. =-= =-= =-= =-= =-= =-= =-= */
/* Main.cpp file description:
* The core of the program and the game,
* main() is where the program starts when it begins running.
* Everything starts here.
*/

#include <iostream>
// (Visual Studio automatically adds this but not every IDE does.)
#include <cmath>

// Very necessary for 3D rendering and general glad/glfw window functions:
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// These are for linear algebra (for rendering and other.)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// (Used for texture and miscellaneous image-related things.)
#include <stb/stb_image.h>

// Our manually coded header files, unique to this project.
#include "Texture.h"
#include "TextureAtlas.h"
#include "shaderClass.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Chunk.h"
#include "Text.h"
#include "AudioSystem.h"
#include "AudioSource.h"
#include "AudioBuffer.h"

// Fox's function used to resize the viewport canvas when you resize the program window.
void framebuffer_size_callback(GLFWwindow* window, int w, int h){
	glViewport(0, 0, w, h);
}

// Declare a function to setup GLFW and return a window.
GLFWwindow* setupGLFW();

int main()
{
	std::cout << "Starting Hatchetflash..." << std::endl;

	// Setup GLFW.
	GLFWwindow* window = setupGLFW();

	// If GLFW failed to setup, it returns NULL. If this happens, we close the program.
	if (window == NULL){
		return -1;
	}

	// Loads GLAD so that it configures opengl, and error checks.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initilize GLAD." << std::endl;
		return -1;
	}

	// Gets the width and height of the window (instead of monitor) after it's created for the viewport, accounting for operating system specific weirdness such as Window's taskbar.
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	// Specifies the viewport of opengl in the window.
	glViewport(0, 0, windowWidth, windowHeight);

	// Gives the game-window it's icon, which also displays in the Windows taskbar.
	stbi_set_flip_vertically_on_load(false);
	GLFWimage windowIconImage;
	windowIconImage.pixels = stbi_load("Resources/Utility_Images/Hatchetflash_Window_Icon_A.png", &windowIconImage.width, &windowIconImage.height, 0, 4);
	glfwSetWindowIcon(window, 1, &windowIconImage);
	stbi_image_free(windowIconImage.pixels);

	// Enable depth testing so things are rendered in the correct order.
	glEnable(GL_DEPTH_TEST);
	// Disables rendering of the back of faces
	glEnable(GL_CULL_FACE);

	std::cout << "Hatchetflash Opengl-window created successfully..." << std::endl;

	// Init audio
	AudioSystem audioSystem;
	
	// Load a song
	AudioBuffer buffer("Resources/Music/RetroFuture Dirty.wav");
	AudioSource music;
	music.queueBuffer(buffer.buffer);

	// If used rather than commented out, unlocks the fps of the window for testing purposes.
	//glfwSwapInterval(0);
	
	// Generates the Shader object using the shaders "defualt.vert" and "default.frag".
	Shader shaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
	Shader textShader("Resources/Shaders/text.vert", "Resources/Shaders/text.frag");

	// (A texture atlas used for testing.)
	TextureAtlas testingTexture("Resources/Thingo_ID_Information/Thing-to-Texture-ID-Map.txt", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	testingTexture.texUnit(shaderProgram, "tex0", 0);

	// Intitializes an imperminant testing mat4 which is used for rotating the cube over time.
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// A chunk to be used for testing out the chunk class.
	Chunk testingChunk(314,0,0,0,testingTexture.ThingIDmap,testingTexture.image_count);
	testingChunk.MakeChunkFilledWithTestingBlocks();
	testingChunk.UpdateChunkMesh();
	
	// Specifies the base color that the window is cleared/drawn-over with.
	glClearColor(0.02f, 0.15f, 0.17f, 1.0f);

	// Used for rendering all text in the window.
	Text text;
	text.initText();
	textShader.Activate();

	// Creates the camera object.
	Camera camera(windowWidth, windowHeight, glm::vec3(0.5f, 0.5f, 2.0f));

	// Setup the camera's perspective.
	glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
	glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


	// Counts the time that will later be used for FPS calculations.
	double FPSTimer = 0.0f;
	// Increments every time the FPS is checked.
	long FPSCnt = 0;
	// (Used for our current method of getting the fps.)
	double last_FPS_time = glfwGetTime();
	// Delta-time. (This is a permanent variable even if the code of getting it may change later.)
	float deltaTime = 1.0f / 60.0f;
	// Average FPS, for displaying.
	float avrgFPS = 0.0f;

	while (!glfwWindowShouldClose(window)) //Checks to see if you've "X-d out" the window.
	{
		// Clears the window canvas with it's basic clear color.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Tells OpenGL which Shader Program to use.
		shaderProgram.Activate();

		// Handles camera inputs.
		camera.Inputs(window, deltaTime);
		// Updates and exports the camera matrix to the Vertex Shader.
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Play music.
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS&&!music.isPlaying()) {
			music.play();
		}
		// Pause music.
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS &&music.isPlaying()) {
			music.pause();
		}

		// Assigns a value to the model uniform; NOTE: Must always be done after activating the Shader Program
		GLuint modelLoc = glGetUniformLocation(shaderProgram.ID, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		// Bind the texture and draw the chunk.
		testingTexture.Bind();
		testingChunk.Draw();

		// Render some text for debugging.
		textShader.Activate();
		if (avrgFPS > 0.0f) {
			text.RenderText(textShader, std::to_string(avrgFPS).append(" FPS"), 5.0f, windowHeight - 45, 1.0f, glm::vec3(0.5, 0.8f, 0.5f));
		}
		text.RenderText(textShader, "\"RetroFuture Dirty\" Kevin MacLeod (incompetech.com)", 5.0f, 90.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.5f));
		text.RenderText(textShader, "Licensed under Creative Commons: By Attribution 4.0 License", 5.0f, 65.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.5f));
		text.RenderText(textShader, "http://creativecommons.org/licenses/by/4.0/", 5.0f, 40.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.5f));
		
		// Shows the half second average of fps in the window's title.
		if (FPSTimer > 0.5f) {
			avrgFPS = 1.0f / (FPSTimer /FPSCnt);
			
			//Sets the veriables used for measuring the FPS back to 0
			FPSTimer = 0.0f;
			FPSCnt = 0;
		}
		// FPS timer incremented by time between frames, the FPS counter is incremented too
		FPSTimer += glfwGetTime() - last_FPS_time;
		FPSCnt++;
		deltaTime = glfwGetTime() - last_FPS_time; //(Updates dt.)
		last_FPS_time = glfwGetTime();
		
		//Swaps the window's back buffer canvas and it's front buffer canvas.
		glfwSwapBuffers(window);
		// Checks for window events.
		glfwPollEvents();
	}
	std::cout << "Closing Hatchetflash..." << std::endl;
	// Cleanly deletes all of the created rendering-based objects.
	testingTexture.Delete();
	shaderProgram.Delete();
	
	// Deletes VAO, VBO and EBO stuff related to the chunk's mesh.
	testingChunk.cleanup();
	
	// Destroys the window, stops glfw stuff and ends the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// Define function to setup GLFW and return a window.
GLFWwindow* setupGLFW(){
	// Initializes glfw and instructs it on it's version and that we will be using it's modern core features.
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

	// Creates the window. (If the 4th argument is filled in with primaryMonitor, having the program open will use the entire direct monitor itself, going into fullscreen mode.)
	GLFWwindow* window = glfwCreateWindow(monitorWidth, monitorHeight, "Hatchetflash - Pre-Alpha [Chunk Testing]", NULL, NULL); //(width, height, name, fullscreen monitor pointer, not-important)
	// (Error checking for whether the glfw window was created successfully.)
	if (window == NULL)
	{
		std::cout << "Failed to create the GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Maximizes the window before beginning to use it, and then prepares a callback for resizing the canvas when you resize the window.
	glfwMaximizeWindow(window);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}
