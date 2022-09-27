/* Model.h file description:
* Defines the Model class, and states all of the functions that it will have as defined in "Model.cpp".
*
* (A model stores meshes as well as other information.)
*/

#pragma once

#include <json/json.hpp>
#include "Mesh.h"
#include "shaderClass.h"

using json = nlohmann::json;

class Model{
public:
    Model(const char* file);

    void cleanup();

    void draw();
private:
    const char* file;
    std::vector<unsigned char> data;
    json JSON;

    std::vector<Mesh> meshes;

    void loadMesh(unsigned int indMesh);

    std::vector<unsigned char> getData();
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);

    std::vector<Vertex> assembleVertices(
        std::vector<glm::vec3> positions,
        std::vector<glm::vec3> normals,
        std::vector<glm::vec2> texUVs
    );

    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};
