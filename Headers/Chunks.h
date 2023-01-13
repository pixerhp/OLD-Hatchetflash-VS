//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Chunks.h file description:
* Defines the Chunk class, which is used to create and do things using chunk objects, which store blocks, a mesh and other related things individual chunks would have.
* Note that most of the functions used for or regarding chunk objects are declared here and/or defined in the "Chunks.cpp" file.
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <vector>
#include <map>
#include <iostream> //(Doesn't seem to need to be stated here, but it's probably best to restate it just-in-case.)

#include "Meshes.h"
#include "BlockTextureAtlas.h"


class Chunk
{
	private:
		Mesh chunkMesh; //(The chunk's mesh which is what's rendered; can be updated using certain functions.)
		//static BlockTextureAtlas& blockTextureAtlas; //(Note that BlockTextureAtlas is a singleton class, so there is only one actual block texture atlas in memory which is used everywhere.)


	public:
		// A list of the variables each chunk object independantly contains:
		uint32_t chunkWorldgenSeed = 314; //(The default chunk object's seed being 314 is an arbitrary choice, it can be any number.)
		uint8_t chunkPiome = 0;
		uint16_t chunkBiome = 0;
		uint8_t chunkChangesCount = 0; //Stores the number of times the blocks or content that the chunk is filled with have been changed whilst it's been loaded.
		int32_t chunkCoordsX = 0;
		int32_t chunkCoordsY = 0;
		int32_t chunkCoordsZ = 0;
		std::vector<uint8_t> defaultChunkMaterial{}; //Used for defining the chunk is defaultly filled with, usually air or water. it's a vector of single byte ints since the material may have extra info.
		// ^^^^ NOTE TO FUTURE SELF, CHANGE THE DEFAULT CHUNK MATERIAL ABOVE TO BE AIR/VACUUM INSTEAD OF HAVING NOTHING DEFINED. DO THIS AFTER STID NUMBERING WORK.
		std::vector<std::vector<uint8_t>> chunkBlockStorage{}; //A vector of vectors of single bytes, used for storing a list of all of the blocks within the chunk.
		

		// The object constructor used for when creating a chunk object. (It's unrelated to world generation, this is just for when the raw class object itself is created.)
		Chunk(uint32_t inputChunkWorldgenSeed = 314, uint8_t inputChunkPiome = 0, uint16_t inputChunkBiome = 0, int32_t inputChunkCoordsX = 0, int32_t inputChunkCoordsY = 0, int32_t inputChunkCoordsZ = 0, std::vector<uint8_t> inputDefaultChunkMaterial = {}, std::vector<std::vector<uint8_t>> inputChunkBlockStorage = {}) {
			chunkWorldgenSeed = inputChunkWorldgenSeed;
			chunkPiome = inputChunkPiome;
			chunkBiome = inputChunkBiome;
			chunkCoordsX = inputChunkCoordsX;
			chunkCoordsY = inputChunkCoordsY;
			chunkCoordsZ = inputChunkCoordsZ;
			defaultChunkMaterial = inputDefaultChunkMaterial;
			chunkBlockStorage = inputChunkBlockStorage;
		}


		// Some public functions which can be used on/with indiviudal chunk objects:

		void Draw(); //(Used to initiate rendering the chunk's mesh, which is actually stored in "chunkMesh" and can be updated by certain functions.)
	
		void MakeChunkFilledWithTestingBlocks(); //(Used to generate a testing chunk as defined however is for dev purposes, won't be used in the actual game.)
	
		void UpdateChunkMesh(); //(Used to update the chunk's mesh/visuals to better represent the current state of the chunk.)

		void cleanup(); //(Used for cleaning up the mesh, more specifically it has to do with VBO VAO EBO stuff.)
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 