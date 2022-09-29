/* Chunk.cpp file description:
* Defines functions and other for chunk (physics) objects.
* 
* (The functions here are also stated in "Chunk.h".)
*/

#include "Chunk.h"
#include <iostream>

// A good function for testing basic functionality of chunk objects.
void Chunk::MakeChunkFilledWithTestBlocks()
{
	int i = 0;
	for (int z = 0; z < 16; z++) {
		for (int x = 0; x < 16; x++){
			for (int y = 0; y < 16; y++){
				i = z * 256 + y * 16 + x; // Convert a set of 3 coordinates into a single index for the block array.
				if (y < x && y > z){ // If this value is true, put a block here.
					blockStorage[i] = 600000000; //UPDATE THE NUMBER HERE LATER WHEN YOU NEXT WORK ON CHUNK STUFF PIXER.
				}
			}
		}
	}
}

// Used to update the mesh of the chunk to match what the visuals of the current chunk info should look like.
void Chunk::UpdateChunkMesh()
{
	// Store the vertices and indices of the mesh while generating.
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// index is used as an offset to help calculate mesh indices.
	int index = 0;
	// i is the index of the block we are currently calculating.
	// up, dn, lt, rt, fd, and bk are the are indices of the blocks adjacent to the main one being calculated.
	int i = 0, up = 0, dn = 0, lt = 0, rt = 0, fd = 0, bk = 0;

	// Loop through all the blocks in the chunk.
	for (int z = 0; z < 16; z++) {
		for (int y = 0; y < 16; y++){
			for (int x = 0; x < 16; x++){
				// Convert a set of 3 coordinates into a single index for the block array.
				// Do this for the current block, and all adjecent ones.
				i = z * 256 + y * 16 + x;
				up = z * 256 + (y + 1) * 16 + x;
				dn = z * 256 + (y - 1) * 16 + x;
				lt = z * 256 + y * 16 + (x - 1);
				rt = z * 256 + y * 16 + (x + 1);
				fd = (z + 1) * 256 + y * 16 + x;
				bk = (z - 1) * 256 + y * 16 + x;

				// Check if this is a solid block.
				if (blockStorage.at(i) == 600000000) {
					// Check if the top face of this block should be drawn.
					if (y + 1 >= 16 || blockStorage.at(up) != 600000000){
						// Reserve room for the new vertices. (This is done for performance.)
						vertices.reserve(vertices.size() + 4);
						// Add all vertices needed for this face.
						vertices.push_back({{1.0f + x, 1.0f + y, 0.0f + z},	 {1.0f, 1.0f},	{1.0f, 1.0f, 1.0f}}); //Top face.
						vertices.push_back({{0.0f + x, 1.0f + y, 0.0f + z},	 {0.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{0.0f + x, 1.0f + y, 1.0f + z},	 {0.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 1.0f + y, 1.0f + z},	 {1.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});

						// Reserve room for the new indices. (This is done for performance.)
						indices.reserve(indices.size() + 6);
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
					if (y - 1 < 0 || blockStorage.at(dn) != 600000000){
						// Reserve room for the new vertices. (This is done for performance.)
						vertices.reserve(vertices.size() + 4);
						// Add all vertices needed for this face.
						vertices.push_back({{0.0f + x, 0.0f + y, 0.0f + z},	 {0.0f, 0.0f},	{1.0f, 1.0f, 1.0f}}); //Bottom face.
						vertices.push_back({{1.0f + x, 0.0f + y, 0.0f + z},	 {1.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 0.0f + y, 1.0f + z},	 {1.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{0.0f + x, 0.0f + y, 1.0f + z},	 {0.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});

						// Reserve room for the new indices. (This is done for performance.)
						indices.reserve(indices.size() + 6);
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
					if (x - 1 < 0 || blockStorage.at(lt) != 600000000){
						// Reserve room for the new vertices. (This is done for performance.)
						vertices.reserve(vertices.size() + 4);
						// Add all vertices needed for this face.
						vertices.push_back({{0.0f + x, 0.0f + y, 0.0f + z},	 {0.0f, 0.0f},	{1.0f, 1.0f, 1.0f}}); //Left face.
						vertices.push_back({{0.0f + x, 1.0f + y, 0.0f + z},	 {0.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{0.0f + x, 1.0f + y, 1.0f + z},	 {1.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{0.0f + x, 0.0f + y, 1.0f + z},	 {1.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});

						// Reserve room for the new indices. (This is done for performance.)
						indices.reserve(indices.size() + 6);
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
					// Check if the right face of this block should be drawn.
					if (x + 1 >= 16 || blockStorage.at(rt) != 600000000){
						// Reserve room for the new vertices. (This is done for performance.)
						vertices.reserve(vertices.size() + 4);
						// Add all vertices needed for this face.
						vertices.push_back({{1.0f + x, 0.0f + y, 0.0f + z},	 {1.0f, 0.0f},	{1.0f, 1.0f, 1.0f}}); //Right face.
						vertices.push_back({{1.0f + x, 1.0f + y, 0.0f + z},	 {1.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 1.0f + y, 1.0f + z},	 {0.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 0.0f + y, 1.0f + z},	 {0.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});

						// Reserve room for the new indices. (This is done for performance.)
						indices.reserve(indices.size() + 6);
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
					if (z + 1 >= 16 || blockStorage.at(fd) != 600000000){
						// Reserve room for the new vertices. (This is done for performance.)
						vertices.reserve(vertices.size() + 4);
						// Add all vertices needed for this face.
						vertices.push_back({{0.0f + x, 0.0f + y, 1.0f + z},	 {0.0f, 0.0f},	{1.0f, 1.0f, 1.0f}}); //Front face.
						vertices.push_back({{0.0f + x, 1.0f + y, 1.0f + z},	 {0.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 1.0f + y, 1.0f + z},	 {1.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 0.0f + y, 1.0f + z},	 {1.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});

						// Reserve room for the new indices. (This is done for performance.)
						indices.reserve(indices.size() + 6);
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
					// Check if the back face of this block should be drawn.
					if (z - 1 < 0 || blockStorage.at(bk) != 600000000){
						// Reserve room for the new vertices. (This is done for performance.)
						vertices.reserve(vertices.size() + 4);
						// Add all vertices needed for this face.
						vertices.push_back({{0.0f + x, 0.0f + y, 0.0f + z},	 {1.0f, 0.0f},	{1.0f, 1.0f, 1.0f}}); //Back face.
						vertices.push_back({{0.0f + x, 1.0f + y, 0.0f + z},	 {1.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 1.0f + y, 0.0f + z},	 {0.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
						vertices.push_back({{1.0f + x, 0.0f + y, 0.0f + z},	 {0.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});

						// Reserve room for the new indices. (This is done for performance.)
						indices.reserve(indices.size() + 6);
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
			}
		}
	}
	// Copy the indices and vertices to the mesh.
	chunkMesh.indices = indices;
	chunkMesh.vertices = vertices;
	// Regenerate the meshes VBO and EBO.
	chunkMesh.regenerateVBOAndEBO();
}

// Draw the chunk.
void Chunk::draw(){
	chunkMesh.draw();
}
