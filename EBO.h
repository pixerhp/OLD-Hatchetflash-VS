/* EBO.h file description:
* Defines the EBO class, and states all of the functions that it will have as defined in "EBO.cpp".
* 
* (EBO stands for "Element Buffer Object". EBOs contain information about the indices of an object.)
*/

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID; //(ID reference of an Elements Buffer Object.)
	// States a constructor which generates an Elements Buffer Object and links it to it's indices.
	EBO(GLuint* indices, GLsizeiptr size);

	// States the existence of some basic functions as defined in "EBO.cpp".
	void Bind();
	void Unbind();
	void Delete();
};
#endif