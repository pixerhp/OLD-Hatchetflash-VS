//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   TextureAtlas.cpp file description:
* Defines methods for a class that can store a collection of textures as one big indexable texture known as a "texture atlas".
* Note that some of the functions are defined in "BlockTextureAtlas.h".
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "BlockTextureAtlas.h"


// A texture atlas object constructor, used when instantiating a texture atlas object.
BlockTextureAtlas::BlockTextureAtlas(const char* mapFile, GLenum inputTextureImageType, GLenum slot, GLenum format, GLenum pixelType)
{
	textureImageType = inputTextureImageType; //(Used for assigning the type of the texture to the texture object.)
	// Used for storing the width, height, and number of color channels of the image:
	int widthImg = 32; //(0 is a default input to make sure that they at least have a number, they should be properly assigned before being used though!)
	int heightImg = 32;
	int numColCh = 4;

	stbi_set_flip_vertically_on_load(true); //(Flips the image as is more appropriate for OpenGL use.)

	// Loads the text file that maps image file names to IDs. (It's named "Thing-to-Texture-ID-Map.txt".)
	std::ifstream f(mapFile);
	if (!f.is_open()) {
		printf("Error: Could not open the MapThingsToTextureID file!");
		throw(new CantLoadMapFileException);
	}

	// (Variables used to parse the map file.)
	int from;
	char junk;
	char line[256];
	std::string imageName;
	std::stringstream s;

	image_count = 0; //Also used in the h file, we might not need to assign it here. /////////////
	std::vector<unsigned char> bytes; //(Used to store all of the data for the textures.)

	// Loads in the textures which are listed in the map file.
	while (!f.eof())
	{
		f.getline(line, 256);
		s << line;
		s >> from >> junk >> imageName;
		s.clear();
		ThingIDmap[from] = image_count;

		// Reads the image from a file path and stores it in raw bytes.
		unsigned char* image = stbi_load(imageName.c_str(), &widthImg, &heightImg, &numColCh, 4);

		if (image == nullptr){ throw(new CantLoadImageException); } //(Error checking in case the image isn't loaded.)

		bytes.insert(bytes.end(), image, image + widthImg * heightImg * 4);

		stbi_image_free(image); //(Deletes the image data in bytes as it is already in the OpenGL "Texture" object now.)

		image_count++;
	}

	//  /|/|   Be safe. Close files.
	// (  ^^> /
	f.close();

	// Generates an OpenGL texture object, and assigns the texture unit.
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(inputTextureImageType, ID);

	// Configures the type of algorithm used to make the image larger or smaller. (Seems to relate/also-relate to mipmapping the textures.)
	glTexParameteri(inputTextureImageType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(inputTextureImageType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures how the texture repeats/wraps for when texture coords exceed 1 or similar (if it should repeat/loop at all.)
	glTexParameteri(inputTextureImageType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(inputTextureImageType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// (These are extra code-lines in case you choose to use "GL_CLAMP_TO_BORDER".
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(inputTextureImageType, 0, GL_RGBA, widthImg, heightImg * image_count, 0, format, pixelType, bytes.data()); //(Assigns the image to the OpenGL "Texture" object.)
	glGenerateMipmap(inputTextureImageType); //(Generates MipMaps of the texture atlas.)

	glBindTexture(inputTextureImageType, 0); //(Unbinds the OpenGL Texture object so that it can't be accidentally modified.)
}


void BlockTextureAtlas::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform); //(Gets the location of the uniform.)
	shader.Activate(); // (Needs to be activated before changing the value of a uniform!)
	glUniform1i(texUni, unit); //(Sets the value of the uniform.)
}


void BlockTextureAtlas::Bind()
{
	glBindTexture(textureImageType, ID);
}


void BlockTextureAtlas::Unbind()
{
	glBindTexture(textureImageType, 0);
}


void BlockTextureAtlas::Delete()
{
	glDeleteTextures(1, &ID);
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 