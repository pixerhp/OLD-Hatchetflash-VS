/* EBO.cpp file description:
* Contains a constructor for the EBO, and the definitions for all of the EBO-related functions sepcified in "EBO.h".
* (EBO stands for "Element Buffer Object". EBOs contain information about the indices of an object.)
* (The functions here are also stated in "EBO.h".)
*/

#include"EBO.h"

// An EBO (Elements Buffer Object) constructor which can generate the object that's linked to all of the indices.
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds the EBO.
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO.
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO.
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}