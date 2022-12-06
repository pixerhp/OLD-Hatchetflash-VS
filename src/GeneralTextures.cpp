//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   GeneralTextures.cpp file description:
* Contains a constructor for textures, which allows images to be used as OpenGL textures.
* (The functions here are also stated in "Texture.h".)
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "GeneralTextures.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType; //(Used for assigning the type of the texture to the texture object.)
	int widthImg, heightImg, numColCh; //(Used for storing the width, height, and number of color channels of the image.)

	// Flips the image so it appears right side up for OpenGL use..
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes.
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 4);

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
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMaps of the image.
	glGenerateMipmap(texType);

	// Deletes the image data in bytes as it is already in the OpenGL "Texture" object now.
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't be accidentally modified.
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform.
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// (needs to be activated before changing the value of a uniform.)
	shader.Activate();
	// Sets the value of the uniform.
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
