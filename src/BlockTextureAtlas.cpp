//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   BlockTextureAtlas.cpp file description:
* Defines methods for a class that can store a collection of textures as one big indexable texture known as a "texture atlas".
* Note that many of the functions here are also declared in "BlockTextureAtlas.h".
* The texture atlas, when creating it from a series of individual textures, is (most likely) created in the order: "FIRST image to LAST image ---> TOP of the ta-image to BOTTOM pf the ta-image".
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "BlockTextureAtlas.h" //Note that this also automatically means we get to work with what's #include-d in the h file.
#include "Logger.h"


// The BlockTextureAtlas object constructor, used when creating a block texture-atlas object (which itself is used by chunk stuff.)
BlockTextureAtlas::BlockTextureAtlas()
{
	/////////////////////////////////////////////////

	const bool showBTAtlasCreationTextInConsole = false; //(Toggles whether debug text is displayed in the console regarding texture atlas object creation; default is false.)
	if (showBTAtlasCreationTextInConsole) {
		Logger::getInstance() << Logger::INFO << "Creating a BlockTextureAtlas object...\n";
	}

	const uint8_t fileDirectoryNameLengthUntilFileName = 25; //Stores the length of a file's full directory name up until the unique name of the file. (Example: The length of "Resources/Block_Textures/" is 25 characters.)
	const uint8_t lengthOfFileExtensionIncludingPeriod = 4; //Stores the character length that each of the textures' file extensions will have, *including the period*. (Example: ".png" is 4 characters.)
	const unsigned short int standardTextureWidth = 32;
	const unsigned short int standardTextureHeight = 32;

	numberOfImagesInTextureAtlas = 0; //(Also initially stated in the "BlockTextureAtlas.h".)
	textureImageType = GL_TEXTURE_2D;

	GLenum GLTextureUnitSlot = GL_TEXTURE0;
	GLenum imageInformationFormat = GL_RGBA;
	GLenum datatypeOfPixelData = GL_UNSIGNED_BYTE;

	/////////////////////////////////////////////////

	std::vector<std::filesystem::path> filePathsVectorList{}; //(Used to store the list of file paths to the image files.)
	std::vector<std::string> imageNamesList{}; //(Used to store the list of image names without the path part or the extension part (which includes not having the period.))

	// Using the folder/directory input, here we get a list of all of the files paths and file names found in the folder/directory. (Both of those things are stored in vectors.)
	for (const auto& entry : std::filesystem::directory_iterator("Resources/Block_Textures/"))
	{
		filePathsVectorList.push_back(entry.path()); //Adds the full file path of a found image to this vector.

		// Adds the unique name of the file without any path or extension stuff to this vector, and then optionally outputs that it found said file to the console.
		imageNamesList.push_back(entry.path().string().substr(fileDirectoryNameLengthUntilFileName, entry.path().string().size() - (fileDirectoryNameLengthUntilFileName + lengthOfFileExtensionIncludingPeriod)));
		if (showBTAtlasCreationTextInConsole) {
			Logger::getInstance() << Logger::INFO << "Discovered texture : " + imageNamesList[imageNamesList.size() - 1] << "\n";
		}

		numberOfImagesInTextureAtlas += 1;
	}
	if (showBTAtlasCreationTextInConsole) {
		Logger::getInstance() << Logger::INFO << "Total texture count: " << numberOfImagesInTextureAtlas << "\n";
	}
	if (showBTAtlasCreationTextInConsole) {
		Logger::getInstance() << Logger::INFO << "Finished creating a list of image file paths and a list of image names. Creating atlas texture...\n";
	}

	/////////////////////////////////////////////////

	std::vector<unsigned char> bytesForTheFullTextureAtlasImage{}; //(Used to store all of the bytes for creating the full big texture atlas image.)

	// the next step is to start making the long line texture atlas image itself, and also make the map which connects the 
	for (std::filesystem::path filePath : filePathsVectorList) //(Loops through each file path.)
	{
		// Some variables used to store information found about the image, preset to what most textures probably will be found to have.
		int imageWidth = 32;
		int imageHeight = 32;
		int numberOfColorChannelsInImage = 4;

		// Gets and stores the bytes of the image.
		unsigned char* imageBytes = stbi_load(filePath.string().c_str(), &imageWidth, &imageHeight, &numberOfColorChannelsInImage, 4);
		if (imageBytes == nullptr) { throw(new CantLoadImageException); } //(Error checking stuff.)

		// Adds the image's bytes to the eventual full texture atlas image's bytes.
		bytesForTheFullTextureAtlasImage.insert(bytesForTheFullTextureAtlasImage.end(), imageBytes, imageBytes + imageWidth * imageHeight * 4); //(Adds the bytes of the image to the main big texture atlas' bytes.)

		stbi_image_free(imageBytes); //(Delete's the loaded stbi image data of the individual image since we don't need the individual image's data anymore.)
	}

	// Generates an OpenGL texture object, and assigns it the texture unit and image type;
	glGenTextures(1, &internalTextureID);
	glActiveTexture(GLTextureUnitSlot);
	glBindTexture(textureImageType, internalTextureID);

	// Configures the mipmapping algorithm. (Mipmaping makes it so that a smaller less detailed texture can be used if it's rendered really small anyways.)
	glTexParameteri(textureImageType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(textureImageType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures how the texture repeats/wraps for when texture coords exceed 1 or similar (if it should repeat/loop at all.)
	glTexParameteri(textureImageType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureImageType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// (These are extra code-lines in case you ever want to use the "GL_CLAMP_TO_BORDER" style.)
	//float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the large texture atlas' image data to the newish OpenGL "Texture" object.
	glTexImage2D(textureImageType, 0, GL_RGBA, standardTextureWidth, standardTextureHeight * numberOfImagesInTextureAtlas, 0, imageInformationFormat, datatypeOfPixelData, bytesForTheFullTextureAtlasImage.data());
	glGenerateMipmap(textureImageType); //(Generates the MipMaps of the image.)

	glBindTexture(textureImageType, 0); //(Unbinds the OpenGL Texture object so that it can't be accidentally modified.)


	if (showBTAtlasCreationTextInConsole) {
		Logger::getInstance() << Logger::INFO << "Atlas texture OpenGL texture object created successfully. Creating texcoord + other maps...\n";
	}

	/////////////////////////////////////////////////

	/// YOU LEFT OFF HERE, YOU GOTTA DO MAP AND STID NUMBERING MAP VARIABLE STUFF HERE. MAKE IT SO THAT YOU CAN ACTUALLY GET TEXTURE COORDINATES AND ALSO SO THAT YOU CAN GET RGB COLOR EFFECT NUMBERS FROM STID NUMBERING.

	/// DOUBLE CHECK LATER TO ENSURE THAT THE TEXCOORDS FROM NAMES THING IS ACTUALLY FUNCTIONALLY CORRECT AND NOT BACKWARDS.


	// Sets up the "imageNameToTexcoordsMap" map.
	for (int i = 0; i < numberOfImagesInTextureAtlas; i++) //(Note that we already know that the order of imageNamesList is the same order as how images were added to the texture atlas.)
	{
		imageNameToTexcoordsMap.insert({ imageNamesList.at(i), ((float)((float)numberOfImagesInTextureAtlas - (float)i) / (float)numberOfImagesInTextureAtlas) });
	}

	if (showBTAtlasCreationTextInConsole) {
		Logger::getInstance() << Logger::INFO << "BlockTextureAtlas object created successfully!\n";
		Logger::getInstance() << Logger::DEBUG << "[To turn off this text, use the showBTAtlasCreationTextInConsole bool in \"BlockTextureAtlas.cpp\".]\n\n";
	}
}


void BlockTextureAtlas::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform); //(Gets the location of the uniform.)
	shader.Activate(); // (Needs to be activated before changing the value of a uniform!)
	glUniform1i(texUni, unit); //(Sets the value of the uniform.)
}


void BlockTextureAtlas::Bind()
{
	glBindTexture(textureImageType, internalTextureID);
}


void BlockTextureAtlas::Unbind()
{
	glBindTexture(textureImageType, 0);
}


void BlockTextureAtlas::Delete()
{
	glDeleteTextures(1, &internalTextureID);
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
