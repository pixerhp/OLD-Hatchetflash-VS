//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   TextureAtlas.cpp file description:
* Defines methods for a class that can store a collection of textures as one big indexable texture known as a "texture atlas".
* Note that some of the functions are defined in "BlockTextureAtlas.h".
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "BlockTextureAtlas.h" //Note that this also automatically means we get to work with what's #include-d in the h file.


// A texture atlas object constructor, used when instantiating a texture atlas object.
BlockTextureAtlas::BlockTextureAtlas(const char* inputFolderDirectory, GLenum inputTextureImageType, GLenum inputGLTextureUnitSlot, GLenum inputImageInformationFormat, GLenum inputDataTypeOfPixelData)
{
	const bool showBlockTextureAtlasObjectCreationTextInConsole = true; //(Toggles whether debug text is displayed in the console regarding texture atlas object creation; default is false.)
	if (showBlockTextureAtlasObjectCreationTextInConsole) { std::cout << "\nCreating a BlockTextureAtlas object..." << std::endl; }

	const uint8_t fileDirectoryNameLengthUntilFileName = 25; //Stores the length of a file's full directory name up until the unique name of the file. (Example: The length of "Resources/Block_Textures/" is 25 characters.)
	const uint8_t lengthOfFileExtensionIncludingPeriod = 4; //Stores the character length that each of the textures' file extensions will have, *including the period*. (Example: ".png" is 4 characters.)

	numberOfImagesInTextureAtlas = 0; //(It is initialized at 0, so this statement isn't actually needed, but it's nice to have here anyways.)
	textureImageType = inputTextureImageType;


	std::vector<std::filesystem::path> filePathsVectorList{}; //(Used to store the list of file paths to the image files.)
	std::vector<std::string> imageNamesList{}; //(Used to store the list of image names without the path part or the extension part (which includes not having the period.))

	// Using the folder/directory input, here we get a list of all of the files paths and file names found in the folder/directory. (Both of those things are stored in vectors.)
	for (const auto& entry : std::filesystem::directory_iterator(inputFolderDirectory))
	{
		filePathsVectorList.push_back(entry.path()); //Adds the full file path of a found image to this vector.

		// Adds the unique name of the file without any path or extension stuff to this vector, and then optionally outputs that it found said file to the console.
		imageNamesList.push_back(entry.path().string().substr(fileDirectoryNameLengthUntilFileName, entry.path().string().size() - (fileDirectoryNameLengthUntilFileName + lengthOfFileExtensionIncludingPeriod)));
		if (showBlockTextureAtlasObjectCreationTextInConsole) { std::cout << "Found texture: " + imageNamesList[imageNamesList.size() - 1] << std::endl; }

		numberOfImagesInTextureAtlas += 1;
	}


	



	if (showBlockTextureAtlasObjectCreationTextInConsole) { std::cout << "BlockTextureAtlas object created successfully!\n(You can turn of blocktextureatlas-loading console text using a bool in \"BlockTextureAtlas.cpp\".)\n" << std::endl; }


	/*
	textureImageType = inputTextureImageType; //(Used for assigning the type of the texture to the texture object.)
	// Used for storing the width, height, and number of color channels of the image:
	int widthImg = 32; //(These are default inputs to make sure that they at least start with something, but they need to be properly assigned later on before being used.)
	int heightImg = 32;
	int numColCh = 4;

	stbi_set_flip_vertically_on_load(true); //(Flips the image as is more appropriate for OpenGL use.)

	// Loads the text file that maps image file names to IDs. (It's named "Thing-to-Texture-ID-Map.txt".)
	std::ifstream f(inputFolderDirectory);
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

		numberOfImagesInTextureAtlas++;
	}

	//  /|/|   Be safe. Close files.
	// (  ^^> /
	f.close();

	// Generates an OpenGL texture object, and assigns the texture unit.
	glGenTextures(1, &ID);
	glActiveTexture(inputGLTextureUnitSlot);
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

	glTexImage2D(inputTextureImageType, 0, GL_RGBA, widthImg, heightImg * image_count, 0, inputImageInformationFormat, inputDataTypeOfPixelData, bytes.data()); //(Assigns the image to the OpenGL "Texture" object.)
	glGenerateMipmap(inputTextureImageType); //(Generates MipMaps of the texture atlas.)

	glBindTexture(inputTextureImageType, 0); //(Unbinds the OpenGL Texture object so that it can't be accidentally modified.) */
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