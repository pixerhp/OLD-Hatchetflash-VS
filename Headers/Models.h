//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Models.h file description:
* Defines the Model class, and states all of the functions that it will have as defined in "Model.cpp".
* (A model stores meshes as well as other information.)
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

/// TODO: Fox didn't really understand all of the code he wrote when following the tutorial.
/// TODO: So therefore fox cannot write any more comments for this file.
/// TODO: So we need to go back to the GLM video to figure out how to comment this.

#pragma once

#include <json/json.hpp>
#include "Meshes.h"
#include "shaderClass.h"
   

// Uncomment this and redo un-undo this change later if desired, note that you'll have to do it a few times in the cpp file too.
// Do this so that we can type `json` instead of `nlohmann::json` each time we use it.
//using json = nlohmann::json;


// Class to load, store, and render a Model.
class Model
{
    public:
        // Constructor takes in a file path to the model file.
        Model(const char* file);

        // Deletes VAO, VBO and EBO for all the meshes in this model.
        void cleanup();

        // Draw all meshes in this model.
        void draw();
    private:
        // Store the file path for the loaded model.
        const char* file;
        std::vector<unsigned char> data;
        nlohmann::json JSON;

        // Store all the meshes for this mode.
        std::vector<Mesh> meshes;

        void loadMesh(unsigned int indMesh);

        std::vector<unsigned char> getData();
        std::vector<float> getFloats(nlohmann::json accessor);
        std::vector<GLuint> getIndices(nlohmann::json accessor);

        std::vector<Vertex> assembleVertices(
            std::vector<glm::vec3> positions,
            std::vector<glm::vec3> normals,
            std::vector<glm::vec2> texUVs
        );

        std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
        std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
        std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 