/* default.frag file description:
* Defines the OpenGL code for the default fragment shader to be used in rendering.
* (The fragment shader here takes in information relating to rendering stuff and processes the final image of pixels.)
* (Also see the shader class for more use.)
*/

#version 330 core
out vec4 FragColor;
void main()
{
	FragColor = vec4(0.32f, 0.56f, 0.80f, 1.0f);
}