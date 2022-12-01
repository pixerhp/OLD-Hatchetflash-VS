/* TextureAtlas.h file description:
*    Declare a class that stores a bunch of textures as one, big, indexable texture.
*/

#pragma once
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

// Declare a class that stores a bunch of textures as one, big, indexable texture.
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

class CantLoadImageException{};
class CantLoadMapFileException{};
