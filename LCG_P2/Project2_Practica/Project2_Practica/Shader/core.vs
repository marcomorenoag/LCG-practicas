#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;	//Aloja el color en una nueva localidad de memoria

out vec3 ourColor;

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = color;
   //vertexShader le manda el color a fragmentColor
}