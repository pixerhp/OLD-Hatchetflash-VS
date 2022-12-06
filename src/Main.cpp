//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= JMJ =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Main.cpp file description:
* Pixer Pinecone.
* The heart of the game's code, main() is where the program starts up from.
* [For information about this project and otherwise, see the "See-also.txt" text file.]
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

// Commonly used basic includes:
#include <iostream>
#include <cmath> //(Visual Studio automatically adds this but not every IDE does.)
#include <vector> //(For creating general dynamic arrays.)
#include <stdint.h> //(Allows for ints of very defined sizes, such as uint8_t or uint16_t or uint32_t.)

// (Used in 3D rendering and glad/glfw window functions.)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// (Used for linear algebra, which itself is mostly used for 3D rendering.)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// (Used for texture loading and image-related functions.)
#include <stb/stb_image.h>

// (Our project's unique header files.)
#include "BlockTextureAtlas.h"
//#include "GeneralTextures.h" //CURRENTLY NOT USED.
#include "ShaderClass.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Chunks.h"
#include "TextRendering.h"
#include "AudioSystem.h"
#include "AudioSource.h"
#include "AudioBuffer.h"


// Function declarations. (Their definitions are below int main().)
GLFWwindow* setupGLFW(); //(Declares a function which sets up GLFW and returns a window.)
void framebuffer_size_callback(GLFWwindow* window, int w, int h); //(Declares a function used to resize the viewport canvas when you resize the program's window.)


int main()
{
	std::cout << "Starting Hatchetflash program...\n" << std::endl;

	/////////////////////////////////////////////////

	bool showDebugUI = true; //(Toggles whether debug UI is shown. Debug UI includes the FPS counter.)

	std::cout << "Adjustable booleans instantiated..." << std::endl;

	/////////////////////////////////////////////////

	// Sets up GLFW and creates the window object.
	GLFWwindow* window = setupGLFW(); //(Uses a function below the main function in "main.cpp" (this code file.))

	// Although these are also intially fetched/set in the setupGLFW() function, it's nice to do it again here so that we still have access to your monitor info. (For example, what if you wanted to full-screen the game?)
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor(); //(Creates a pointer to the primary monitor you're using (in case you'd like to reference/use it more directly later.))
	const GLFWvidmode* monitorVideoMode = glfwGetVideoMode(primaryMonitor); //(Gets the video-mode information of your primary monitor (which includes screen size.))
	int monitorWidth = monitorVideoMode->width; int monitorHeight = monitorVideoMode->height; //(Initializes "monitorWidth" and "monitorHeight" to the respective dimensions of your monitor.)

	if (window == NULL) //(Error-checking: if GLFW failed to setup, it's function will return NULL. We check for if we get a NULL and close the program if we do.)
	{
		std::cout << "FATAL ERROR: Failed set up GLFW window." << std::endl;
		return -1; 
	}

	// Loads GLAD such that it configures opengl, and also error checks. (Closes the program if GLAD didn't load properly.)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "FATAL ERROR: Failed to initilize GLAD." << std::endl;
		return -1;
	}

	std::cout << "Successfully set-up GLFW and initialized GLAD..." << std::endl;

	/////////////////////////////////////////////////

	// Gets and stores the width & height of the window after it's created to be used for the viewport. (instead of the size of your raw monitor, which fixes a Windows task-bar issue.)
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	glViewport(0, 0, windowWidth, windowHeight); //(Specifies opengl's viewport for the window.)

	// Gives the window it's corner-icon (which is also used for the Windows taskbar icon image.)
	stbi_set_flip_vertically_on_load(false); //(Normally this needs to be true for textures and rendering, but in this case it needs to be false.)
	GLFWimage windowIconImage;
	windowIconImage.pixels = stbi_load("Resources/Utility_Images/Hatchetflash_Window_Icon_A.png", &windowIconImage.width, &windowIconImage.height, 0, 4);
	glfwSetWindowIcon(window, 1, &windowIconImage);
	stbi_image_free(windowIconImage.pixels);

	std::cout << "Hatchetflash Opengl-window created..." << std::endl;

	/////////////////////////////////////////////////

	glEnable(GL_DEPTH_TEST); //(Enables depth testing, which makes sure that things are drawn on top of eachother correctly.)
	glEnable(GL_CULL_FACE); //(Disables rendering the backs of faces.)
	//glfwSwapInterval(0); //(If not commented out, unlocks the window's fps. Should only be turned on temporarily for testing purposes.)
	glClearColor(0.02f, 0.15f, 0.17f, 1.0f); //(Specifies the color that the window is cleared / drawn-over with each frame.)

	std::cout << "Hatchetflash glEnable settings set..." << std::endl;

	/////////////////////////////////////////////////

	// Generates the Shader object using the shaders "defualt.vert" and "default.frag".
	Shader shaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
	Shader textShader("Resources/Shaders/text.vert", "Resources/Shaders/text.frag");

	// Used to render any/all text in the program's window.
	Text textRenderer;
	textRenderer.initText();
	textShader.Activate();

	std::cout << "Hatchetflash shader-objects created..." << std::endl;

	/////////////////////////////////////////////////

	double FPSTimer = 0.0f; //(Used for counting the time; used in FPS-related calculations.
	long FPSCnt = 0; //(Increments each time the program's FPS is checked.)
	double last_FPS_time = glfwGetTime(); //(Used in FPS calculations.)
	double deltaTime = 1.0f / 60.0f; //(Delta-time. It's not used for very much right now, but it will be integral to the game's movement and physics in the future.)
	double avrgFPS = 60.0f; //(The program's average FPS from the last batch of frames, this is what's displayed when the fps is stated.)
	bool buttonHeld = false; //(Used to detect if a button was pressed, but only so we check it once per press.)

	std::cout << "Hatchetflash time and FPS variables instantiated..." << std::endl;

	/////////////////////////////////////////////////

	AudioSystem audioSystem; //(Initializes the audio system stuff, currently required for playing audio.)
	
	// Loads some testing audio. (Currently, "Gymnopedie No 1".)
	AudioBuffer buffer("Resources/Music/Gymnopedie-No-1.wav"); //NOTE, SOME OF THE VARIABLE NAMES HERE CAN PROBABLY BE RENAMED TO BE MUCH BETTER.
	AudioSource music;
	music.queueBuffer(buffer.buffer);

	std::cout << "Hatchetflash audio instantiated..." << std::endl;

	/////////////////////////////////////////////////

	// Creates the camera object.
	Camera viewCam(windowWidth, windowHeight, glm::vec3(0.0f, 20.0f, 80.0f)); //(Also initializes the camera's position to where you start out already seeing the blocks. This will change later.)

	// Set's up the view-camera's perspective.
	glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
	glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	std::cout << "Hatchetflash view-camera object instantiated..." << std::endl;

	/////////////////////////////////////////////////

	// A texture atlas used for chunks' block textures.
	BlockTextureAtlas chunkBlocksTextureAtlas("Resources/Block_Textures/", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	chunkBlocksTextureAtlas.texUnit(shaderProgram, "tex0", 0);

	std::cout << "Hatchetflash textures and texture-atlases loaded..." << std::endl;

	std::cout << "State an image name and I'll tell you it's top-left texcoord." << std::endl;
	std::string testingString;
	std::cin >> testingString;
	auto it = chunkBlocksTextureAtlas.imageNameToTexcoordsMap.find(testingString);
	std::cout << "Texcoord top-left num: " << it->first << " = " << it->second << std::endl;

	/////////////////////////////////////////////////

	glm::mat4 modelMatrix = glm::mat4(1.0f); //(Currently used for positioning chunks.)

	// Creates a cube/prism of chunk objects to be used for testing.
	std::vector<Chunk> chunks;
	for (int z = 0; z < 4; z++){
	for (int y = 0; y < 4; y++){
	for (int x = 0; x < 4; x++){
		chunks.push_back(Chunk{314,x,y,z}); //(initializes a chunk objects.)
	} //end x
	} //end y
	} //end z
	
	// Fills the chunks' block-slots with random blocks and refreshes their meshes. 
	for (Chunk& chunk: chunks){
		//chunk.MakeChunkFilledWithTestingBlocks();
		//chunk.UpdateChunkMesh(); //// COMMENTED OUT DUE TO IT NOT CURRENTLY WORKING!
	}

	std::cout << "Hatchetflash pre-while-loop initializations ran..." << std::endl;

	/////////////////////////////////////////////////

	std::cout << "\nMain while loop reached, starting Hatchetflash!\n" << std::endl;

	while (!glfwWindowShouldClose(window)) //(Checks if you've prompted closing out the window. (One example would be "X-ing out the window".))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //(Clears/fills the window's canvas with the set gl clear color.)
		shaderProgram.Activate(); //(Tells OpenGL which Shader Program to use.)


		viewCam.Inputs(window, deltaTime); //(Checks and handles view-camera key inputs.)

		// (Updates and exports the camera's matrix to the Vertex Shader to be used in rendering.)
		viewCam.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");


		// When you press the 'f' key, the default song will play.
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS&&!music.isPlaying()) { music.play(); }
		// When you press the 'f' key, the playing song will pause.
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS &&music.isPlaying()) { music.pause(); }


		// Toggles the debug UI if the 'F1' key is pressed.
		if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS){
			if (!buttonHeld) { showDebugUI = !showDebugUI; }
			buttonHeld = true;
		}else{
			buttonHeld = false;
		}


		// Assigns a value to the model uniform. NOTE: MUST ALWAYS BE DONE *AFTER* ACTIVATING THE SHADER PROGRAM. //Also, model uniform??
		GLuint modelLoc = glGetUniformLocation(shaderProgram.ID, "modelMatrix");

		// Binds the texture atlas used for chunk blocks and draws the chunks.
		chunkBlocksTextureAtlas.Bind();
		for (Chunk& chunk: chunks){ //(Cycles through and runs code for all chunks.)
			modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3{chunk.chunkCoordsX * 4, chunk.chunkCoordsY * 4, chunk.chunkCoordsZ * 4});
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			chunk.Draw();
		}

		
		// Sets the displayed FPS to the half-second average of the programs's FPS.
		if (FPSTimer > 0.5f) {
			avrgFPS = 1.0f / (FPSTimer/FPSCnt);
			
			// (Sets the veriables used for measuring the FPS back to 0.)
			FPSTimer = 0.0f;
			FPSCnt = 0;
		}

		// FPS timer incremented by time between frames, the FPS counter is incremented too
		FPSTimer += glfwGetTime() - last_FPS_time;
		FPSCnt++;
		deltaTime = glfwGetTime() - last_FPS_time; //(Updates delta-time.)
		last_FPS_time = glfwGetTime();


		if (showDebugUI) //(If showDebugUI is set to true, render debug text.)
		{
			textRenderer.RenderText(textShader, std::to_string(avrgFPS).append(" avg-FPS"), 5.0f, windowHeight - 45, 1.0f, glm::vec3(0.5, 0.8f, 0.5f));

			textRenderer.RenderText(textShader, "Press 'f' for: \"Gymnopedie No 1\" Kevin MacLeod (incompetech.com)", 5.0f, 90.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.5f));
			textRenderer.RenderText(textShader, "Licensed under Creative Commons: By Attribution 4.0 License", 5.0f, 65.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.5f));
			textRenderer.RenderText(textShader, "http://creativecommons.org/licenses/by/4.0/", 5.0f, 40.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.5f));
		}
		

		glfwSwapBuffers(window); //(Swaps the window's back buffer canvas with it's front buffer canvas.)
		glfwPollEvents(); //(Checks for / gets window-events, such as attempting to close the window.)
	}

	/////////////////////////////////////////////////

	std::cout << "\nEnding Hatchetflash program..." << std::endl;


	// Deletes all of the renderable objects:
	chunkBlocksTextureAtlas.Delete();

	// Deletes all of the created rendering-based objects:
	shaderProgram.Delete();
	textShader.Delete();
	
	// Deletes chunk meshes' related VAO, VBO and EBO stuff:
	for (Chunk& chunk: chunks){
		chunk.cleanup();
	}
	

	// Destroys the window, stops glfw-related things and fully ends the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Hatchetflash program successfully ended." << std::endl;
	return 0;

	/////////////////////////////////////////////////
}





// A function used to resize the viewport canvas when you resize the program's window. (Thanks again, Fox!)
void framebuffer_size_callback(GLFWwindow* window, int w, int h) { glViewport(0, 0, w, h); }


/* A function which sets up GLFW and returns a window object.
* (Used early on in the main function.)
*/
GLFWwindow* setupGLFW()
{
	// Initializes glfw and instructs it on what version it is, and that we'll be using only it's modern (non-legacy) core features.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Fetches and sets info regarding your primary monitor. (The temp. version of the variables, the more perminant ones are in main().)
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor(); //(Creates a pointer to the primary monitor you're using (in case you'd like to reference/use it more directly later.))
	const GLFWvidmode * monitorVideoMode = glfwGetVideoMode(primaryMonitor); //(Gets the video-mode information of your primary monitor (which includes screen size.))
	int monitorWidth = monitorVideoMode->width; int monitorHeight = monitorVideoMode->height; //(Initializes "monitorWidth" and "monitorHeight" to the respective dimensions of your monitor.)

	// Creates the window. (If the 4th argument is filled in with a pointer to your primary-monitor, the program will fill and mess with you entire monitor itself, AKA fullscreen mode.)
	GLFWwindow* window = glfwCreateWindow(monitorWidth, monitorHeight, "Hatchetflash   -   [Pre-Alpha Designing & Development]", NULL, NULL); //(width, height, name, fullscreen monitor pointer, not-important)
	if (window == NULL) //(Error-checks whether the glfw window was created successfully or not.)
	{
		std::cout << "Failed to create the GLFW window! (created window object == NULL)" << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Maximizes the window before beginning to use it, and then prepares a callback for resizing the canvas when you resize the window.
	glfwMaximizeWindow(window);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 