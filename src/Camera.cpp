//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Camera.cpp file description:
* Contains a contructor for the Camera Object, a function for calculating camera matrix math and checks keyboard and mouse inputs for camera movement.
* (The functions here are also stated in "Camera.h".)
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "Camera.h"


// A simple constructor for the camera object.
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::cameraWindowWidth = width;
	Camera::cameraWindowHeight = height;
	Position = position;
}

// Runs camera matrix calculations and sends the results to the vertex shader for rendering.
void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	// Initializes these matrices as otherwise they would be the "null" matrix.
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Has camera look in the right orientation from the right position.
	view = glm::lookAt(Position, Position + Orientation, UpDirection);
	// Adds perspective to the scene.
	projection = glm::perspective(glm::radians(FOVdeg), (float)cameraWindowWidth / cameraWindowHeight, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader.
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

// Checks keyboard and mouse inputs as used for camera movement.
void Camera::Inputs(GLFWwindow* window, float dt)
{
	// Re-get the actual size of the window.
	glfwGetWindowSize(window, &cameraWindowWidth, &cameraWindowHeight);

	if (cameraWindowWidth == 0){ cameraWindowWidth = 1; }
	if (cameraWindowHeight == 0){ cameraWindowHeight = 1; }

	// (Keyboard inputs.)
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Collisions::testPColl(Position, (movementSpeed * dt) * Orientation, plane(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), 0), AABB(glm::vec3(-0.3f, -0.3f, -0.3f), glm::vec3(0.3f, 0.3f, 0.3f)));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += (movementSpeed * dt) * -glm::normalize(glm::cross(Orientation, UpDirection));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += (movementSpeed * dt) * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += (movementSpeed * dt) * glm::normalize(glm::cross(Orientation, UpDirection));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		Position += (movementSpeed * dt) * glm::normalize(glm::cross(Orientation, glm::normalize(glm::cross(Orientation, UpDirection)))); //THIS CAN PROBABLY BE SIMPLIFIED.
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		Position += (movementSpeed * dt) * glm::normalize(glm::cross(Orientation, glm::normalize(glm::cross(Orientation, -UpDirection)))); //THIS CAN PROBABLY BE SIMPLIFIED.
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += (movementSpeed * dt) * UpDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Position += (movementSpeed * dt) * -UpDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		movementSpeed = 40.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		movementSpeed = 10.0f;
	}

	// (Mouse inputs.)
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// Hides the mouse cursor.
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Used to prevent the camera persepctive from jumping when you initially click.
		if (firstClick)
		{
			glfwSetCursorPos(window, (cameraWindowWidth / 2), (cameraWindowHeight / 2));
			firstClick = false;
		}

		// Stores and fetches the coordinates of the cursor.
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen, and then "transforms" them into degrees.
		float rotX = turningSensitivity * (float)(mouseY - (cameraWindowHeight / 2)) / cameraWindowHeight;
		float rotY = turningSensitivity * (float)(mouseX - (cameraWindowWidth / 2)) / cameraWindowWidth;

		// Calculates the upcoming vertical change in the Orientation due to mouse movements.
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, UpDirection)));

		// Determines whether the next vertical Orientation is legal or not.
		if (std::abs(glm::angle(newOrientation, UpDirection) - glm::radians(90.0f)) <= glm::radians(85.0f)) //(85 degrees is the set vertical limit here.)
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation leftwards/rightwards.
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), UpDirection);

		// Sets mouse cursor to the middle of the screen such that it doesn't end up roaming around as you turn the camera.
		glfwSetCursorPos(window, (cameraWindowWidth / 2), (cameraWindowHeight / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Unhides cursor when the camera is not looking around anymore.
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		// Ensures that the next time the camera looks around the cursor doesn't jump.
		firstClick = true;
	}
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 