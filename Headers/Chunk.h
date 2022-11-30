//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Chunk.h file description:
* Defines the Chunk class which is used for chunk objects, which store blocks and a mesh and related things.
* Has the initializer for when chunk objects are first created, and states all of a chunk's functions as most are defined in "Chunk.cpp".
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <vector>
#include <map>
#include "Mesh.h"


class Chunk {
private:
	Mesh chunkMesh; //(The chunk's mesh which is what's rendered; can be updated using certain functions.)

public:
	std::map<int, int> ThingIDmap;
	int ThingIDsize;
	unsigned long int seed = 314;
	int chunkX = 0;
	int chunkY = 0;
	int chunkZ = 0;
	std::vector<unsigned int> blockStorage[4096]; //(Contains an array of 4096 (16^3) unsigned int vectors, which can allow for each array slot (block position in a chunk) to contain multiple actual block thingos.

	// The constructor for chunk objects. (Unrelated to how they we be after worldgen stuff, this is just when the raw object is created.)
	Chunk(unsigned long int input_seed, int input_chunkX, int input_chunkY, int input_chunkZ, std::map<int, int> input_ThingIDmap, int input_ThingIDsize) : blockStorage() {
		seed = input_seed;
		chunkX = input_chunkX;
		chunkY = input_chunkY;
		chunkZ = input_chunkZ;
		ThingIDmap = input_ThingIDmap;
		ThingIDsize = input_ThingIDsize;
	}

	void Draw(); //(Used to initiate rendering the chunk's mesh, which is actually stored in "chunkMesh" and can be updated by certain functions.)
	
	void MakeChunkFilledWithTestingBlocks(); //(Used to generate a testing chunk as defined however is for dev purposes, won't be used in the actual game.)
	
	void UpdateChunkMesh(); //(Used to update the chunk's mesh/visuals to better represent the current state of the chunk.)

    void cleanup(); //(Used for cleaning up the mesh, more specifically it has to do with VBO VAO EBO stuff.)
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 