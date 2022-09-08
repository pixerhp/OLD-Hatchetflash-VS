/* default.vert file description:
* Defines the OpenGL code for the default vertex shader to be used in rendering.
* (The vertex shader here takes in the lists of vertices, indices and other information and processes the shape made out of them and how it would be displayed.)
* (Also see the shader class for more use.)
*/

#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}