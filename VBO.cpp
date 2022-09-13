/* VBO.cpp file description:
* Contains a constructor for the VBO, and the definitions for all of the VBO-related functions sepcified in "VBO.h".
* (VBO stands for "Vertex Buffer Object". VBOs contain information about the vertices of an object.)
* (The functions here are also stated in "VBO.h".)
*/

#include"VBO.h"

// A constructor which generates a Vertex Buffer Object and links it to vertices.
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO.
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO.
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO.
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}