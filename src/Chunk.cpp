/* Chunk.cpp file description:
* Defines functions and other for chunk (physics) objects.
* 
* (The functions here are also stated in "Chunk.h".)
*/

#include "Chunk.h"

// A good function for testing basic functionality of chunk objects.
void Chunk::MakeChunkFilledWithTestBlocks()
{
	for (int i = 0; i < 4096; i++) {
		blockStorage[i] = {600000000}; //UPDATE THE NUMBER HERE LATER WHEN YOU NEXT WORK ON CHUNK STUFF PIXER.
	}
}

// Used to update the mesh of the chunk to match what the visuals of the current chunk info should look like.
void Chunk::UpdateChunkMesh()
{
	for (int i = 0; i < 4096; i++) {
		if (blockStorage[i].at(0) == 600000000);
		{
			//CREATE VERTEX STUFF FOR A BASIC CUBE BASED ON 'i' FOR THE MESH.
		}
	}
}