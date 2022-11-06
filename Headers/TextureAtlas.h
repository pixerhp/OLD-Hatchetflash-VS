/* Texture.h file description:
* Defines the Texture class, and states all of the functions that it will have.
* (The functions for this class are definied in "Texture.cpp".)
*/

#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class TextureAtlas
{
public:
	GLuint ID;
	GLenum type;
	TextureAtlas(const char* folder, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// States a function which assigns a texture unit to a texture.
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	
	// States some basic functions as defined in "Texture.cpp".
	void Bind();
	void Unbind();
	void Delete();
};
