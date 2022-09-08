/* VAO.cpp file description:
* Contains a constructor for the VAO, and the definitions for all of the VAO-related functions sepcified in "VAO.h".
* (VAO stands for "Vertex Array Object". VAOs contain VBOs and information about the complete rendered object and vertex bindings.)
* (The functions here are also stated in "VAO.h".)
*/

#include"VAO.h"

// A constructor which generates a VAO ID.
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout.
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO.
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO.
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO.
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}