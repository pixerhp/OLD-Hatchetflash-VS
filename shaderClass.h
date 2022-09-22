/* shaderClass.cpp file description:
* Defines the shader class, and states all of it's functions (which are defined in "shaderClass.cpp".)
* (A shader in this context makes default.frag and default.vert usable alongside the VBO, EBO and VAO, and texture information.)
*/

#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

// States a function which reads the contents of a file.
std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID; //(ID reference of a Shader Class Object.)
	// States a constructor which generates a Shader Program from 2 different shaders.
	Shader(const char* vertexFile, const char* fragmentFile);
	
	void Activate();

	void Delete();

private:
	// Checks for if the different Shaders have compiled properly.
	void compileErrors(unsigned int shader, const char* type);
};

// (Used in "shaderClass.cpp" for throwing a pretty recognizable error for when/if the shaderProgram can't read file contents properly.)
class ShaderNotFoundException{};
