/* Mesh.cpp file description:
*
* A Mesh stores information about and generates meshes.
*/

#include "Mesh.h"

// Regenerate the VBO and EBO with the vertices and indices vectors.
void Mesh::regenerateVBOAndEBO(){
    // Bind the VAO.
    glBindVertexArray(VAOID);

    // Create the VBO and EBO.
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);

    // Fill the VBO and EBO with the vertex and index data.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GLusage);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GLusage);

    // Unbind VAO, VBO, and EBO.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Draw the mesh.
void Mesh::draw(){
    // Bind the VAO.
    glBindVertexArray(VAOID);

    // Draw the mesh.
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO.
    glBindVertexArray(0);
}

// Delete the VAO, VBO, and EBO.
void Mesh::cleanup(){
    glDeleteVertexArrays(1, &VAOID);
    glDeleteBuffers(1, &VBOID);
    glDeleteBuffers(1, &EBOID);
}
