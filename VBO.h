/* VBO.h file description:
* Defines the VBO class, and states all of the functions that it will have as defined in "VBO.cpp".
* 
* (VBO stands for "Vertex Buffer Object". VBOs contain information about the vertices of an object.)
*/

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	GLuint ID; //(ID reference for a Vertex Buffer Object.)
	// States a constructor which generates an Vertex Buffer Object and links it to it's vertices.
	VBO(GLfloat* vertices, GLsizeiptr size);

	// States the existence of some basic functions as defined in "VBO.cpp".
	void Bind();
	void Unbind();
	void Delete();
};
#endif