/* Mesh.cpp file description:
*
* A Mesh stores information about and generates meshes.
*/

// {Jcodefox will comment this file soon.}

#include "Mesh.h"
#include <glad/glad.h>

void Mesh::regenerateVBOsAndEBOs(){
    glBindVertexArray(VAOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GLusage);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GLusage);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw(){
    glBindVertexArray(VAOID);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::cleanup(){
    // Delete VAOs, VBOs, and EBOs.
    glDeleteVertexArrays(1, &VAOID);
    glDeleteBuffers(1, &VBOID);
    glDeleteBuffers(1, &EBOID);
}
