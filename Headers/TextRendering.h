//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   TextRendering.h file description:
* Declare a class that handles text rendering.
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once
#pragma comment(lib, "freetype.lib")
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <map>
#include <string>
#include <glm/ext/matrix_clip_space.hpp>
#include "shaderClass.h"
#include FT_FREETYPE_H  


struct Character
{
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


// Defines a class which handles text-based rendering.
class Text 
{
    public:
        unsigned int VAO, VBO;
        std::map<char, Character> Characters;
	    void initText();
        void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 