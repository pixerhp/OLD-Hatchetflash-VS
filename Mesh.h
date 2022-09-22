/* Mesh.h file description:
* Defines the Mesh class, and states all of the functions that it will have as defined in "Mesh.cpp".
*
* A Mesh stores information about and generates meshes.
*/

#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

// Store the Vertex data as a struct, this makes it easier to change and work with.
struct Vertex{
    glm::vec3 position;
    glm::vec2 textUV;
};

class Mesh{
private:
    // This determines how often the data will be sent to the GPU, this is for potential use in the future.
    // Do not remove.
    GLenum GLusage = GL_STATIC_DRAW;
public:
    // Vectors to store all vertices and indices.
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    // The IDs of the VAO, VBO, and EBO.
    GLuint VAOID;
    GLuint VBOID;
    GLuint EBOID;

    Mesh(std::vector<Vertex> vertices = {}, std::vector<GLuint> indices = {});

    // Regenerate the VBO and EBO with the vertices and indices vectors.
    void regenerateVBOAndEBO();

    // Draw the mesh.
    void draw();

    // Delete the VAO, VBO, and EBO.
    void cleanup();
};
