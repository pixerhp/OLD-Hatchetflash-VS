/* Chunk.h file description:
* Defines the Chunk class, and states all of the functions that it will have as defined in "Chunk.cpp".
*/

#pragma once

#include <vector>
#include <map>
#include "Mesh.h"

class Chunk {
private:

	// The chunk's mesh to be rendered, which can be updated using "UpdateChunkMesh()".
	Mesh chunkMesh;

public:
	std::map<int, int> ThingIDmap;
	int ThingIDsize;
	unsigned long int seed = 0;
	int chunkX = 0;
	int chunkY = 0;
	int chunkZ = 0;
	std::vector<unsigned int> blockStorage[4096]; //(Contains an array of 4096 (16^3) unsigned int vectors, which can allow for each array slot (block position in a chunk) to contain multiple actual block thingos.

	// A constructor function for chunk objects (independant from the actual terrain generation.)
	Chunk(unsigned long int input_seed, int input_chunkX, int input_chunkY, int input_chunkZ, std::map<int, int> input_ThingIDmap, int input_ThingIDsize) : blockStorage() {
		seed = input_seed;
		chunkX = input_chunkX;
		chunkY = input_chunkY;
		chunkZ = input_chunkZ;
		ThingIDmap = input_ThingIDmap;
		ThingIDsize = input_ThingIDsize;
	}

	// Used to initiate rendering of the chunk's mesh (which is stored in "chunkMesh".)
	void Draw();
	// Used to generate the chunk with blocks as defined for testing, probably usually independantly of the chunk's seed.
	void MakeChunkFilledWithTestingBlocks();
	// Used to update the chunk's mesh/visuals to better represent the current state of the chunk.
	void UpdateChunkMesh();

	// Cleans up the mesh.
    void cleanup();
};
