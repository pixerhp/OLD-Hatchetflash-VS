/* default.vert file description:
* Defines the OpenGL code for the default vertex shader to be used in rendering.
*
* Takes in information such as positions, colors and texture coordinates as needed for some rendering.
* (Outputs information to the default fragment shader: "default.frag".)
*/

#version 330 core //(Helps OpenGL with version and related info.)

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Texture Coordinates
layout (location = 1) in vec2 aTex;
// Color
layout (location = 2) in vec3 aColor;


// Outputs different information to the fragment shader.
out vec2 texCoord;
out vec3 color;

// Takes in the matrix outputed by the camera object.
uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main()
{
	// Outputs the positions/coordinates of all of the vertices.
	gl_Position = camMatrix * modelMatrix * vec4(aPos, 1.0f);
	// Assigns the texture coordinates from the Vertex Data to "texCoord".
	texCoord = aTex;

	color = aColor;
}
