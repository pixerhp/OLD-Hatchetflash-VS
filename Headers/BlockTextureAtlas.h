//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   TextureAtlas.h file description:
* A texture atlas is a large texture composed of a bunch of smaller textures, such as a grid of block textures in this case.
* Many of the functions are defined in "BlockTextureAtlas.cpp".
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"


// Declares a class which can store a bunch of textures as one big indexable texture, known as the/a "texture atlas".
class TextureAtlas
{
	public:
		unsigned int image_count;
		GLuint ID;
		GLenum textureImageType;
		std::map<int, int> ThingIDmap;
		TextureAtlas(const char* folder, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	
		// States a function which assigns a texture unit to a texture.
		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		
		// States some basic functions as defined in "Texture.cpp".
		void Bind();
		void Unbind();
		void Delete();
};

class CantLoadImageException{}; //(Currently used for error related stuff.)
class CantLoadMapFileException{}; //(Currently used for error related stuff.)

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 