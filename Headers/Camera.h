//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Camera.h file description:
* Defines the Camera class, and states all of the functions that it will have as defined in "Camera.cpp".
* (An instance of a camera object is used as the in-game perspective camera.)
* (The used camera object also currently contains the movement controls.)
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderClass.h"
#include "Collisions.h"


class Camera
{
	public:
		// Stores the main vectors of the camera.
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 UpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

		// Used to prevent the camera from jumping around when first clicking right click.
		bool firstClick = true;
		// (Stores the width and height of the window for the camera to use.)
		int cameraWindowWidth;
		int cameraWindowHeight;

		// The speed of the camera's orientational movement + it's sensitivity to turning around.
		float movementSpeed = 10.0f;
		float turningSensitivity = 200.0f;

		// States a camera object constructor which sets up initial values.
		Camera(int width, int height, glm::vec3 position);
		// States a function which updates/calculates and exports the camera matrix to the Vertex Shader.
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		// States a function which handles camera mouse/keyboard inputs.
		void Inputs(GLFWwindow* window, float dt);
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 