/* TextureAtlas.cpp file description:
*   Define methods for a class that stores a bunch of textures as one, big, indexable texture.
*/


#include "BlockTextureAtlas.h"

TextureAtlas::TextureAtlas(const char* mapFile, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType; //(Used for assigning the type of the texture to the texture object.)
	int widthImg, heightImg, numColCh; //(Used for storing the width, height, and number of color channels of the image.)

	// Flips the image so it appears right side up for OpenGL use..
	stbi_set_flip_vertically_on_load(true);

	// Load in the file that maps image file names to ids
	std::ifstream f(mapFile);
	if (!f.is_open()) {
		printf("Error: \"Could not open the bloody MapThingsToTextureID file, too bad!\"");
		throw(new CantLoadMapFileException);
	}

	// Variables to parse the map file.
	int from;
	char junk;
	char line[256];
	std::string imageName;
	std::stringstream s;

	// The amount of images loaded.
	image_count = 0;

	// All the data for the textures.
	std::vector<unsigned char> bytes;

	// Load in the textures listed in the map file.
	while (!f.eof())
	{
		f.getline(line, 256);
		s << line;
		s >> from >> junk >> imageName;
		s.clear();
		ThingIDmap[from] = image_count;

		// Reads the image from a file and stores it in bytes.
		unsigned char* image = stbi_load(imageName.c_str(), &widthImg, &heightImg, &numColCh, 4);

		if (image == nullptr){
			throw(new CantLoadImageException);
		}

		bytes.insert(bytes.end(), image, image + widthImg * heightImg * 4);

		// Deletes the image data in bytes as it is already in the OpenGL "Texture" object now.
		stbi_image_free(image);

		image_count++;
	}

	//  /|/|   Be safe. Close files.
	// (  ^^> /
	f.close();

	// Generates an OpenGL texture object, and assigns the texture unit.
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm used to make the image larger or smaller.
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures how the texture repeats/wraps for when texture coords exceed 1 or similar (if it should repeat/loop at all.)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// (These are extra code-lines in case you choose to use "GL_CLAMP_TO_BORDER".
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL "Texture" object.
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg * image_count, 0, format, pixelType, bytes.data());
	// Generates MipMaps of the image.
	glGenerateMipmap(texType);

	// Unbinds the OpenGL Texture object so that it can't be accidentally modified.
	glBindTexture(texType, 0);
}

void TextureAtlas::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform.
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// (needs to be activated before changing the value of a uniform.)
	shader.Activate();
	// Sets the value of the uniform.
	glUniform1i(texUni, unit);
}

void TextureAtlas::Bind()
{
	glBindTexture(type, ID);
}

void TextureAtlas::Unbind()
{
	glBindTexture(type, 0);
}

void TextureAtlas::Delete()
{
	glDeleteTextures(1, &ID);
}
