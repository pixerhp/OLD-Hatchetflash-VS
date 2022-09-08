/* shaderClass.cpp file description:
* Defines the shader class, and states all of the functions that it will have.
* (A shader in this context makes default.frag and default.vert usable alongside the VBO, EBO and VAO.)
* (The functions for this class are definied in "shaderClass.cpp".)
*/

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

// States the existance of a function which reads the contents of a file.
std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID; //(ID reference of a Shader Class Object.)
	// States a constructor which generates a Shader Program from 2 different shaders.
	Shader(const char* vertexFile, const char* fragmentFile);

	// States the existence of some basic functions as defined in "shaderClass.cpp".
	void Activate();
	void Delete();
private:
	// Checks if the different Shaders have compiled properly.
	void compileErrors(unsigned int shader, const char* type);
};

//Used in "shaderClass.cpp" for linux for throwing a pretty recognizable error for when/if the shaderProgram can't read file contents properly.
class ShaderNotFoundException{};
#endif
