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
class BlockTextureAtlas
{
	public:
		// (Some variables that the texture atlas object stores.)
		unsigned int image_count = 0; //(Used to know how many total textures are in the texture atlas.)
		GLuint ID;
		GLenum textureImageType;
		std::map<int, int> ThingIDmap;

		BlockTextureAtlas(const char* inputFolderDirectory, GLenum inputTextureType, GLenum inputGLTextureUnitSlot, GLenum inputImageInformationFormat, GLenum inputDataTypeOfPixelData); //States a constructor for a texture atlas object.
	
		void texUnit(Shader& shader, const char* uniform, GLuint unit); //(States a function which assigns a texture unit to a texture.)
		
		// Custom functions which relate to fetching textures and related from material and related STID numbers.
		void getTextureCoordinatesFromTwoStidNumbers();
		void getRGBColorEffectNumbersFromTwoStidNumbers();

		// States some basic functions as defined in "Texture.cpp".
		void Bind();
		void Unbind();
		void Delete();
};

class CantLoadImageException{}; //(Currently used for error related stuff.)
class CantLoadMapFileException{}; //(Currently used for error related stuff.)

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 