/* default.vert file description:
* Defines the OpenGL code for the default vertex shader to be used in rendering.
*
* Takes in information such as positions, colors and texture coordinates as needed for some rendering.
* (Outputs information to the default fragment shader: "default.frag".)
*/

#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;


// Outputs different information to the fragment shader.
out vec3 color;
out vec2 texCoord;

// Takes in the matrix outputed by the camera object.
uniform mat4 camMatrix;

void main()
{
	// Outputs the positions/coordinates of all of the vertices.
	gl_Position = camMatrix * vec4(aPos,1.0f);
	// Assigns the colors from the Vertex Data to "color".
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord".
	texCoord = aTex;
}
