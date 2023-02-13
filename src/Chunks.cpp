//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Chunks.cpp file description:
* Defines functions and related for cubic chunk objects, which store the blocks and world-stuff that you see in the game.
* (The functions here are also stated in "Chunks.h".)
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "Chunks.h"
#include "Logger.h"


// A function used to initiate drawing the chunk's mesh.
void Chunk::Draw(){ chunkMesh.draw(); }


//THE REASON THAT ALL OF THIS IS COMMENTED OUT IS THAT IT IS ARCHAIC, AS THE NEW METHODS FOR CHUNK GENERATION STILL HAVE TO BE DESIGNED.
// Generates a chunk filled with whatever blocks are defined as needed for pure testing/dev related purposes, won't be used in-game.
void Chunk::MakeChunkFilledWithTestingBlocks()
{
	int seed = 314 + 64 * chunkCoordsZ + 16 * chunkCoordsY + 4 * chunkCoordsX;
	srand(seed);
	int index = 0;
	for (int z = 0; z < 4; z++) {
	for (int y = 0; y < 4; y++) {
	for (int x = 0; x < 4; x++) {

		// Converts the set of 3 coordinates into a single index as used for the block array.
		index = 16*z + 4*y + x;

		if (index >= chunkBlockStorage.size()){
			chunkBlockStorage.push_back({});
		}

		chunkBlockStorage[index].push_back(80 + rand() % 17 - 1); //Set's the block's thingo-ID to a basic one.

	} //(End of the 'x' for loop.)
	} //(End of the 'y' for loop.)
	} //(End of the 'z' for loop.)
}


void Chunk::GenerateMarchingCubesMesh(){
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	int vertex_bottom_left_back;
	int vertex_bottom_right_back;
	int vertex_top_left_back;
	int vertex_top_right_back;

	int vertex_bottom_left_front;
	int vertex_bottom_right_front;
	int vertex_top_left_front;
	int vertex_top_right_front;

	int id = 0;

	int index = 0;

	for (int z = 0; z < 3; z++) {
	for (int y = 0; y < 3; y++) {
	for (int x = 0; x < 3; x++) {
		vertex_bottom_left_back = (z + 0) * 16 + (y + 0) * 4 + (x + 0);
		vertex_bottom_right_back = (z + 0) * 16 + (y + 0) * 4 + (x + 1);
		vertex_top_left_back = (z + 0) * 16 + (y + 1) * 4 + (x + 0);
		vertex_top_right_back = (z + 0) * 16 + (y + 1) * 4 + (x + 1);

		vertex_bottom_left_front = (z + 1) * 16 + (y + 0) * 4 + (x + 0);
		vertex_bottom_right_front = (z + 1) * 16 + (y + 0) * 4 + (x + 1);
		vertex_top_left_front = (z + 1) * 16 + (y + 1) * 4 + (x + 0);
		vertex_top_right_front = (z + 1) * 16 + (y + 1) * 4 + (x + 1);

		id = (chunkBlockStorage[vertex_bottom_left_back][0] >= 80) | (chunkBlockStorage[vertex_bottom_right_back][0] >= 80) << 1 | (chunkBlockStorage[vertex_top_left_back][0] >= 80) << 2 | (chunkBlockStorage[vertex_top_right_back][0] >= 80) << 3 | (chunkBlockStorage[vertex_bottom_left_front][0] >= 80) << 4 | (chunkBlockStorage[vertex_bottom_right_front][0] >= 80) << 5 | (chunkBlockStorage[vertex_top_left_front][0] >= 80) << 6 | (chunkBlockStorage[vertex_top_right_front][0] >= 80) << 7;

		Logger::getInstance() << Logger::DEBUG << id << "\n";

		if (id != 0 && id != 255) {
			vertices.push_back({{1.0f + x, 1.0f + y, 0.0f + z},	 {1.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});
			vertices.push_back({{0.0f + x, 1.0f + y, 0.0f + z},	 {0.0f, 0.0f},	{1.0f, 1.0f, 1.0f}});
			vertices.push_back({{0.0f + x, 1.0f + y, 1.0f + z},	 {0.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});
			vertices.push_back({{1.0f + x, 1.0f + y, 1.0f + z},	 {1.0f, 1.0f},	{1.0f, 1.0f, 1.0f}});

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

	chunkMesh.vertices = vertices;
	chunkMesh.indices = indices;
	chunkMesh.regenerateVBOAndEBO();
}

// Used to update the chunk's mesh/visuals to better represent the current state of the chunk.
/*
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
	for (int z = 0; z < 4; z++) {
	for (int y = 0; y < 4; y++) {
	for (int x = 0; x < 4; x++) {
		// Converts a set of 3 coordinates into a single index for the block array.
		// Do this for the current block, and all adjecent ones.
		i = z * 16 + y * 4 + x;
		up = z * 16 + (y + 1) * 4 + x;
		dn = z * 16 + (y - 1) * 4 + x;
		lt = z * 16 + y * 4 + (x - 1);
		rt = z * 16 + y * 4 + (x + 1);
		fd = (z + 1) * 16 + y * 4 + x;
		bk = (z - 1) * 16 + y * 4 + x;

		float UV_Y_A = ThingIDmap[chunkBlockStorage[i][0]] / (float)ThingIDsize;
		float UV_Y_B = (ThingIDmap[chunkBlockStorage[i][0]] + 1.0f) / (float)ThingIDsize;

		// Checks if the block is a valid block we know how to work with.
		if (chunkBlockStorage[i][0] >= 800000000) {
			// Check if the top face of this block should be drawn.
			if (y + 1 >= 4 || chunkBlockStorage[up][0] < 800000000){
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
			if (y - 1 < 0 || chunkBlockStorage[dn][0] < 800000000){
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
			if (x - 1 < 0 || chunkBlockStorage[lt][0] < 800000000){
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
			if (x + 1 >= 4 || chunkBlockStorage[rt][0] < 800000000){
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
			if (z + 1 >= 4 || chunkBlockStorage[fd][0] < 800000000){
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
			if (z - 1 < 0 || chunkBlockStorage[bk][0] < 800000000){
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
} */


// A function used to initiate cleaning up the chunk's mesh, which would mean deleting it's VAO, VBO, and EBO stuff.
void Chunk::cleanup(){ chunkMesh.cleanup(); }

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
