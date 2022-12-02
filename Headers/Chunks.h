//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Chunk.h file description:
* Defines the Chunk class which is used for chunk objects, which store blocks and a mesh and related things.
* Has the initializer for when chunk objects are first created, and states all of a chunk's functions as most are defined in "Chunks.cpp".
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <vector>
#include <map>

#include "Mesh.h"
#include "BlockTextureAtlas.h"


class Chunk
{
	private:
		Mesh chunkMesh; //(The chunk's mesh which is what's rendered; can be updated using certain functions.)
		static BlockTextureAtlas chunkBlocksTextureAtlas; /////////////////////////ASSIGN THIS TO A PROPER ACTUAL TEXTURE ATLAS LATER USING A CHUNK OBJECT IN MAIN!!!


	public:
		// A list of the variables each chunk object independantly contains:
		uint32_t chunkWorldgenSeed = 314; //(The default chunk object's seed being 314 is an arbitrary choice, it can be any number.)
		uint8_t chunkPiome = 0;
		uint16_t chunkBiome = 0;
		uint8_t chunkChangesCount = 0; //Stores the number of times the blocks or content that the chunk is filled with have been changed whilst it's been loaded.
		int32_t chunkCoordsX = 0;
		int32_t chunkCoordsY = 0;
		int32_t chunkCoordsZ = 0;
// NOTE TO SELF FOR THE FUTURE: CHANGE THE DEFAULT CHUNK MATERIAL TO AIR INSTEAD OF NOTHING LATER WHEN YOU CAN!
		std::vector<uint8_t> defaultChunkMaterial{}; //Used for defining the chunk is defaultly filled with, usually air or water. it's a vector of single byte ints since the material may have extra info.
		std::vector<std::vector<uint8_t>> chunkBlockStorage{}; //A vector of vectors of single bytes, used for storing a list of all of the blocks within the chunk.
		

		// A selection of different chunk-object constructors. (It's unrelated to world generation, this is just for when the raw class object itself is created.)
		Chunk() {
		}
		Chunk(uint32_t inputChunkWorldgenSeed, int32_t inputChunkCoordsX, int32_t inputChunkCoordsY, int32_t inputChunkCoordsZ) {
			chunkWorldgenSeed = inputChunkWorldgenSeed;
			chunkCoordsX = inputChunkCoordsX;
			chunkCoordsY = inputChunkCoordsY;
			chunkCoordsZ = inputChunkCoordsZ;
		}
		Chunk(uint32_t inputChunkWorldgenSeed, int32_t inputChunkCoordsX, int32_t inputChunkCoordsY, int32_t inputChunkCoordsZ, std::vector<uint8_t> inputDefaultChunkMaterial, std::vector<std::vector<uint8_t>> inputChunkBlockStorage) {
			chunkWorldgenSeed = inputChunkWorldgenSeed;
			chunkCoordsX = inputChunkCoordsX;
			chunkCoordsY = inputChunkCoordsY;
			chunkCoordsZ = inputChunkCoordsZ;
			defaultChunkMaterial = inputDefaultChunkMaterial;
			chunkBlockStorage = inputChunkBlockStorage;
		}
		Chunk(uint32_t inputChunkWorldgenSeed, uint8_t inputChunkPiome, uint16_t inputChunkBiome, int32_t inputChunkCoordsX, int32_t inputChunkCoordsY, int32_t inputChunkCoordsZ) {
			chunkWorldgenSeed = inputChunkWorldgenSeed;
			chunkPiome = inputChunkPiome;
			chunkBiome = inputChunkBiome;
			chunkCoordsX = inputChunkCoordsX;
			chunkCoordsY = inputChunkCoordsY;
			chunkCoordsZ = inputChunkCoordsZ;
		}
		Chunk(uint32_t inputChunkWorldgenSeed, uint8_t inputChunkPiome, uint16_t inputChunkBiome, int32_t inputChunkCoordsX, int32_t inputChunkCoordsY, int32_t inputChunkCoordsZ, std::vector<uint8_t> inputDefaultChunkMaterial, std::vector<std::vector<uint8_t>> inputChunkBlockStorage) {
			chunkWorldgenSeed = inputChunkWorldgenSeed;
			chunkPiome = inputChunkPiome;
			chunkBiome = inputChunkBiome;
			chunkCoordsX = inputChunkCoordsX;
			chunkCoordsY = inputChunkCoordsY;
			chunkCoordsZ = inputChunkCoordsZ;
			defaultChunkMaterial = inputDefaultChunkMaterial;
			chunkBlockStorage = inputChunkBlockStorage;
		}

	void Draw(); //(Used to initiate rendering the chunk's mesh, which is actually stored in "chunkMesh" and can be updated by certain functions.)
	
	void MakeChunkFilledWithTestingBlocks(); //(Used to generate a testing chunk as defined however is for dev purposes, won't be used in the actual game.)
	
	void UpdateChunkMesh(); //(Used to update the chunk's mesh/visuals to better represent the current state of the chunk.)

    void cleanup(); //(Used for cleaning up the mesh, more specifically it has to do with VBO VAO EBO stuff.)
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 