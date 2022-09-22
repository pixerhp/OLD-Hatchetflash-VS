/* Chunk.h file description:
* 
*/

#pragma once

#include <vector>

class Chunk
{
public:

	unsigned long int seed = 0;
	int chunkX = 0;
	int chunkY = 0;
	std::vector<unsigned int> blockStorage[4096];

	/* A constructor for chunk objects.
	* 
	* Seed specifies the seed the chunk is generated from.
	* chunkX and chunkY specify the chunk coordinates of the chunk for easier later use in generation and functions.
	*/
	Chunk(unsigned long int input_seed, int input_chunkX, int input_chunkY) {
		seed = input_seed;
		chunkX = input_chunkX;
		chunkY = input_chunkY;
	}
};