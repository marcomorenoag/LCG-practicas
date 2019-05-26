#version 330 core
in vec3 ourColor; //recibe un vector3 y lo saca como un vector ourColor

out vec4 color;

void main()
{
	//color = vec4(0.0f,1.0f,1.0f, 1.0f);
	color = vec4(ourColor, 1.0f);
}