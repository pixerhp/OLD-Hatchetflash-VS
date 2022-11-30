/* Chunk.cpp file description:
* Defines functions and related for cubic chunk objects, which store the blocks and world-stuff that you see in the game.
* (The functions here are also stated in "Chunk.h".)
*/

#include "Chunk.h"
#include <iostream>

// Used to initiate drawing the chunk's mesh.
void Chunk::Draw()
{
	chunkMesh.draw();
}

// Generates a very basic chunk which can be used for developer-testing purposes.
void Chunk::MakeChunkFilledWithTestingBlocks()
{
	int seed = 409600*chunkZ + 25600*chunkY + 16*chunkX;
	srand(seed);
	int index = 0;
	for (int z = 0; z < 16; z++) {
	for (int y = 0; y < 16; y++) {
	for (int x = 0; x < 16; x++) {

		// Converts the set of 3 coordinates into a single index as used for the block array.
		index = 256*z + 16*y + x;

		blockStorage[index].push_back(800000000 + rand()%17 - 1); //Set's the block's thingo-ID to a basic one.

	} //(End of the 'x' for loop.)
	} //(End of the 'y' for loop.)
	} //(End of the 'z' for loop.)
}

// Used to update the chunk's mesh/visuals to better represent the current state of the chunk.
void Chunk::UpdateChunkMesh()
{
	// Used to store the vertices and indices of the new mesh being created.
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	int index = 0; //(Used as an offset to help calculate mesh indices.)
	// ('i' is the index of the block we are currently calculating in the array.)
	// (up, dn, lt, rt, fd, and bk are the are indices of the blocks adjacent to the main one being calculated.)
	int i = 0, up = 0, dn = 0, lt = 0, rt = 0, fd = 0, bk = 0;

	// Loops through all of the chunk's blocks, looping the the x primarily, then y's, then z's.
	for (int z = 0; z < 16; z++) {
	for (int y = 0; y < 16; y++) {
	for (int x = 0; x < 16; x++) {
		// Converts a set of 3 coordinates into a single index for the block array.
		// Do this for the current block, and all adjecent ones.
		i = z * 256 + y * 16 + x;
		up = z * 256 + (y + 1) * 16 + x;
		dn = z * 256 + (y - 1) * 16 + x;
		lt = z * 256 + y * 16 + (x - 1);
		rt = z * 256 + y * 16 + (x + 1);
		fd = (z + 1) * 256 + y * 16 + x;
		bk = (z - 1) * 256 + y * 16 + x;

		float UV_Y_A = ThingIDmap[blockStorage[i][0]] / (float)ThingIDsize;
		float UV_Y_B = (ThingIDmap[blockStorage[i][0]] + 1.0f) / (float)ThingIDsize;

		// Checks if the block is a valid block we know how to work with.
		if (blockStorage[i][0] >= 800000000) {
			// Check if the top face of this block should be drawn.
			if (y + 1 >= 16 || blockStorage[up][0] < 800000000){
				// Add all vertices needed for this face.ThingIDsize
				vertices.push_back({{1.0f + x, 1.0f + y, 0.0f + z},	 {1.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}}); //Top face.
				vertices.push_back({{0.0f + x, 1.0f + y, 0.0f + z},	 {0.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{0.0f + x, 1.0f + y, 1.0f + z},	 {0.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 1.0f + y, 1.0f + z},	 {1.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}});

				// Reserve room for the new indices. (This is done for performance.)
				//indices.reserve(indices.size() + 6);
				// Add all indices needed for this face.
				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 3);
				indices.push_back(index + 1);
				indices.push_back(index + 2);
				// Add to the index offset.
				index += 4;
			}
			// Check if the bottom face of this block should be drawn.
			if (y - 1 < 0 || blockStorage[dn][0] < 800000000){
				// Add all vertices needed for this face.
				vertices.push_back({{0.0f + x, 0.0f + y, 0.0f + z},	 {0.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}}); //Bottom face.
				vertices.push_back({{1.0f + x, 0.0f + y, 0.0f + z},	 {1.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 0.0f + y, 1.0f + z},	 {1.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{0.0f + x, 0.0f + y, 1.0f + z},	 {0.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});

				// Reserve room for the new indices. (This is done for performance.)
				//indices.reserve(indices.size() + 6);
				// Add all indices needed for this face.
				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 3);
				indices.push_back(index + 1);
				indices.push_back(index + 2);
				// Add to the index offset.
				index += 4;
			}
			// Check if the left face of this block should be drawn.
			if (x - 1 < 0 || blockStorage[lt][0] < 800000000){
				// Add all vertices needed for this face.
				vertices.push_back({{0.0f + x, 0.0f + y, 0.0f + z},	 {0.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}}); //Left face.
				vertices.push_back({{0.0f + x, 1.0f + y, 0.0f + z},	 {0.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{0.0f + x, 1.0f + y, 1.0f + z},	 {1.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{0.0f + x, 0.0f + y, 1.0f + z},	 {1.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}});

				// Reserve room for the new indices. (This is done for performance.)
				//indices.reserve(indices.size() + 6);
				// Add all indices needed for this face.
				indices.push_back(index);
				indices.push_back(index + 3);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 2);
				indices.push_back(index + 1);
				// Add to the index offset.
				index += 4;
			}
			// Check if the right face of this block should be drawn.
			if (x + 1 >= 16 || blockStorage[rt][0] < 800000000){
				// Add all vertices needed for this face.
				vertices.push_back({{1.0f + x, 0.0f + y, 0.0f + z},	 {1.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}}); //Right face.
				vertices.push_back({{1.0f + x, 1.0f + y, 0.0f + z},	 {1.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 1.0f + y, 1.0f + z},	 {0.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 0.0f + y, 1.0f + z},	 {0.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}});

				// Reserve room for the new indices. (This is done for performance.)
				//indices.reserve(indices.size() + 6);
				// Add all indices needed for this face.
				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 3);
				indices.push_back(index + 1);
				indices.push_back(index + 2);
				// Add to the index offset.
				index += 4;
			}
			// Check if the front face of this block should be drawn.
			if (z + 1 >= 16 || blockStorage[fd][0] < 800000000){
				// Add all vertices needed for this face.
				vertices.push_back({{0.0f + x, 0.0f + y, 1.0f + z},	 {0.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}}); //Front face.
				vertices.push_back({{0.0f + x, 1.0f + y, 1.0f + z},	 {0.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 1.0f + y, 1.0f + z},	 {1.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 0.0f + y, 1.0f + z},	 {1.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}});

				// Reserve room for the new indices. (This is done for performance.)
				//indices.reserve(indices.size() + 6);
				// Add all indices needed for this face.
				indices.push_back(index);
				indices.push_back(index + 3);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 2);
				indices.push_back(index + 1);
				// Add to the index offset.
				index += 4;
			}
			// Check if the back face of this block should be drawn.
			if (z - 1 < 0 || blockStorage[bk][0] < 800000000){
				// Add all vertices needed for this face.
				vertices.push_back({{0.0f + x, 0.0f + y, 0.0f + z},	 {1.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}}); //Back face.
				vertices.push_back({{0.0f + x, 1.0f + y, 0.0f + z},	 {1.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 1.0f + y, 0.0f + z},	 {0.0f, UV_Y_B},	{1.0f, 1.0f, 1.0f}});
				vertices.push_back({{1.0f + x, 0.0f + y, 0.0f + z},	 {0.0f, UV_Y_A},	{1.0f, 1.0f, 1.0f}});

				// Reserve room for the new indices. (This is done for performance.)
				//indices.reserve(indices.size() + 6);
				// Add all indices needed for this face.
				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 3);
				indices.push_back(index + 1);
				indices.push_back(index + 2);
				// Add to the index offset.
				index += 4;
			}
		}
		else //(If the block's thingo-ID is not a valid one we know how to work with.)
		{
			
		}
	} //(End of the 'x' for loop.)
	} //(End of the 'y' for loop.)
	} //(End of the 'z' for loop.)

	// Copies the stored vertices and indices to the mesh.
	chunkMesh.vertices = vertices;
	chunkMesh.indices = indices;
	// Regenerate the mesh's VBO and EBO now that the mesh has changed.
	chunkMesh.regenerateVBOAndEBO();
}

// Cleans up the mesh.
void Chunk::cleanup(){
	chunkMesh.cleanup();
}
