//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   ShaderClass.cpp file description:
* Makes the vertex shader and fragment shader usable by our proram.
* (A shader in this context makes default.frag and default.vert usable alongside the VBO, EBO and VAO.)
* (The functions here are also stated in "ShaderClass.h".)
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "ShaderClass.h"
#include "Logger.hpp"

// Reads a text file and outputs a string with everything in the said text file.
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(new ShaderNotFoundException); //A recognizable error for when/if the shaderProgram can't read the file contents properly.
}

// A constructor that builds the Shader Program from 2 different shaders. (The vertex shader and the fragment shader.)
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Reads vertexFile and the fragmentFile and stores the two strings.
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Converts the shader source strings into constant character arrays.
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Creates a Vertex Shader Object and gets its reference.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attaches the Vertex Shader source code to the Vertex Shader Object.
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compiles the Vertex Shader into more immediately usable machine code.
	glCompileShader(vertexShader);

	// Creates a Fragment Shader Object and gets its reference.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attaches the Fragment Shader source code to the Fragment Shader Object.
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compiles the Vertex Shader into more immediately usable machine code.
	glCompileShader(fragmentShader);

	// Creates a Shader Program Object and gets its referencea
	ID = glCreateProgram();
	// Attaches the Vertex and Fragment Shaders to the Shader Program.
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wraps-up/Links all of the shaders together into the Shader Program.
	glLinkProgram(ID);

	// Deletes the now useless Vertex and Fragment Shader objects.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program.
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program.
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Checks if the different Shaders have compiled properly.
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores the status of the compilation:
	GLint hasCompiled;
	// Character array that the error message can be stored in:
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			Logger::Log(Logger::ERROR) << "SHADER COMPILATION ERROR for:" << type << "\n" << infoLog << "\n";
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			Logger::Log(Logger::ERROR) << "SHADER LINKING ERROR for:" << type << "\n" << infoLog << "\n";
		}
	}
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
