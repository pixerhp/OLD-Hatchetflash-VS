/* VAO.h file description:
* Defines the VAO class, and states all of the functions that it will have as defined in "VAO.cpp".
* 
* (VAO stands for "Vertex Array Object". VAOs contain VBOs and information about the complete rendered object and vertex bindings.)
*/

#pragma once

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID; //(ID reference for a Vertex Array Object.)
	// States a constructor which generates a Vertex Array Object and generates a VAO ID.
	VAO();

	// States the existence of a function which links a VBO to the VAO using a certain layout.
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	// States the existence of some basic functions as defined in "VAO.cpp".
	void Bind();
	void Unbind();
	void Delete();
};
