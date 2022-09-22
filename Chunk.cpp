/* Chunk.h file description:
*
*/

#include "Chunk.h"

void Chunk::MakeChunkFilledWithTestBlocks()
{
	for (int i = 0; i < 4096; i++) {
		blockStorage[i] = {13}; //(13 is chosen as the number for testing-blocks to reserve the first 12 number for other odd-er later use.)
	}
}

void Chunk::UpdateChunkMesh()
{

}