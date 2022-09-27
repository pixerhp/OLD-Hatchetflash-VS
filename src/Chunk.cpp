/* Chunk.cpp file description:
* Defines functions and other for chunk (physics) objects.
* 
* (The functions here are also stated in "Chunk.h".)
*/

#include "Chunk.h"

void Chunk::MakeChunkFilledWithTestBlocks()
{
	for (int i = 0; i < 4096; i++) {
		blockStorage[i] = {600000000}; //(13 is chosen as the number for testing-blocks to reserve the first 12 number for other odd-er later use.)
	}
}

void Chunk::UpdateChunkMesh()
{
	for (int i = 0; i < 4096; i++) {
		if (blockStorage[i].at(0) == 600000000);
		{
			//CREATE VERTEX STUFF FOR A BASIC CUBE BASED ON 'i' FOR THE MESH.
		}
	}
}