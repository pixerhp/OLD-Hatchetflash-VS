/* TextureAtlas.h file description:
*    Very similar to a Texture, but holds loads in many textures into one.
*/

#pragma once
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class TextureAtlas
{
public:
	unsigned int image_count;
	GLuint ID;
	GLenum type;
	std::map<int, int> ThingIDmap;
	TextureAtlas(const char* folder, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// States a function which assigns a texture unit to a texture.
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	
	// States some basic functions as defined in "Texture.cpp".
	void Bind();
	void Unbind();
	void Delete();
};
