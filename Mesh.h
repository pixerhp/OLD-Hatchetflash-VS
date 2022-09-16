/* Mesh.h file description:
* Defines the Mesh class, and states all of the functions that it will have as defined in "Mesh.cpp".
*
* A Mesh stores information about and generates meshes.
*/

// Jcodefox will comment this file soon.

#pragma once

#include <vector>
#include <glad/glad.h>

class Mesh{
    private:
        GLenum GLusage = GL_DYNAMIC_DRAW;
    public:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        GLuint VAOID;
        GLuint VBOID;
        GLuint EBOID;

        Mesh(){
            glGenVertexArrays(1, &VAOID);
            glBindVertexArray(VAOID);

            glGenBuffers(1, &VBOID);
            glGenBuffers(1, &EBOID);

            regenerateVBOsAndEBOs();

            glBindVertexArray(VAOID);
            glBindBuffer(GL_ARRAY_BUFFER, VBOID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
        }

        void regenerateVBOsAndEBOs();

        void draw();

        void cleanup();
};
