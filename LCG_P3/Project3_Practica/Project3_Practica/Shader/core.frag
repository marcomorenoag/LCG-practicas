#version 330 core
in vec3 ourColor; //recibe un vector3 y lo saca como un vector ourColor

out vec4 color;

void main()
{
	color = vec4(ourColor, 1.0f);
}