/* Mesh.cpp file description:
*
* (A Mesh stores information about vertices and such and generates meshes.)
* (The functions here are also stated in "Mesh.h".)
*/

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    // Generate and bind the VAO.
    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);

    // Generate the VBO and EBO.
    glGenBuffers(1, &VBOID);
    glGenBuffers(1, &EBOID);

    // Populate the VBO and EBO with passed in data.
    regenerateVBOAndEBO();

    // Rebind the VAO, VBO, and EBO. (The regenerateVBOsAndEBOs function unbound them.)
    glBindVertexArray(VAOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);

    // Set the VAO information.
    // First 3 floats are position.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Second 2 floats are texture coordinates.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO, VBO, and EBO.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Regenerate the VBO and EBO with the vertices and indices vectors.
void Mesh::regenerateVBOAndEBO(){
    // Binds the VAO.
    glBindVertexArray(VAOID);

    // Creates the VBO and EBO.
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);

    // Fills the VBO and EBO with the vertex and index data.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GLusage);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GLusage);

    // Unbinds VAO, VBO, and EBO.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Draw the mesh.
void Mesh::draw(){
    // Binds the VAO.
    glBindVertexArray(VAOID);

    // Draws the mesh.
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbinds the VAO.
    glBindVertexArray(0);
}

// Deletes the VAO, VBO, and EBO.
void Mesh::cleanup(){
    glDeleteVertexArrays(1, &VAOID);
    glDeleteBuffers(1, &VBOID);
    glDeleteBuffers(1, &EBOID);
}
