#include "Model.h"

Model::Model(const char* file){
    std::string text = get_file_contents(file);
    JSON = json::parse(text);

    Model::file = file;
    data = getData();

    for (unsigned int i = 0; i < JSON["meshes"].size(); i++){
        loadMesh(i);
    }
}

void Model::cleanup(){
    for (unsigned int i = 0; i < JSON["meshes"].size(); i++){
        meshes[i].cleanup();
    }
}

void Model::draw(){
    for (unsigned int i = 0; i < JSON["meshes"].size(); i++){
        meshes[i].draw();
    }
}

void Model::loadMesh(unsigned int indMesh){
    unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
    unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

    std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
    std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
    std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
    std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
    std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
    std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);

    std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
    std::vector<GLuint> indicies = getIndices(JSON["accessors"][indAccInd]);

    meshes.push_back(Mesh(vertices, indicies));
}

std::vector<unsigned char> Model::getData(){
    std::string bytesText;
    std::string uri = JSON["buffers"][0]["uri"];

    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
    bytesText = get_file_contents((fileDirectory + uri).c_str());

    // I have no idea why another identical string is created here, but it's what the tutorial said to do...
    std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
    return data;
}

std::vector<float> Model::getFloats(json accessor){
    std::vector<float> floatVec;

    unsigned int buffViewInd = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    std::string  type = accessor["type"];

    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int numPerVert;
    if (type == "SCALAR") numPerVert = 1;
    else if (type == "VEC2") numPerVert = 2;
    else if (type == "VEC3") numPerVert = 3;
    else if (type == "VEC4") numPerVert = 4;
    else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

    unsigned int beginningOfData = byteOffset + accByteOffset;
    unsigned int lengthOfData = count * 4 * numPerVert;
    for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i){
        unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
        float value;
        // Convert bytes to a float and store in the value variable.
        std::memcpy(&value, bytes, sizeof(float));
        floatVec.push_back(value);
    }

    return floatVec;
}

std::vector<GLuint> Model::getIndices(json accessor){
    std::vector<GLuint> indices;

    unsigned int buffViewInd = accessor.value("bufferView", 0);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    unsigned int componentType = accessor["componentType"];

    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int beginningOfData = byteOffset + accByteOffset;

    if (componentType == 5125){
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i){
            unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
            unsigned int value;
            // Convert bytes to an unsigned int and store in the value variable.
            std::memcpy(&value, bytes, sizeof(unsigned int));
            indices.push_back((GLuint)value);
        }
    }else if (componentType == 5123){
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i){
            unsigned char bytes[] = { data[i++], data[i++] };
            unsigned short value;
            // Convert bytes to an unsigned int and store in the value variable.
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.push_back((GLuint)value);
        }
    }else if (componentType == 5122){
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i){
            unsigned char bytes[] = { data[i++], data[i++] };
            short value;
            // Convert bytes to an unsigned int and store in the value variable.
            std::memcpy(&value, bytes, sizeof(short));
            indices.push_back((GLuint)value);
        }
    }

    return indices;
}

std::vector<Vertex> Model::assembleVertices(
    std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> texUVs
){
    std::vector<Vertex> vertices;
    for (int i = 0; i < positions.size(); i++){
        // TODO: Add normals[i] if we add normals to the game.
        vertices.push_back({positions[i], texUVs[i]});
    }
    return vertices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec){
    std::vector<glm::vec2> vectors;
    for (int i = 0; i < floatVec.size(); i){
        vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec){
    std::vector<glm::vec3> vectors;
    for (int i = 0; i < floatVec.size(); i){
        vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec){
    std::vector<glm::vec4> vectors;
    for (int i = 0; i < floatVec.size(); i){
        vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}
