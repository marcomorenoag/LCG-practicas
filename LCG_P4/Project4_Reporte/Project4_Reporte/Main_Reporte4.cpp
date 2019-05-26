#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Reporte P4, MAMG, PERSONAJE: TRISTEZA", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection

	//GLfloat vertices[] = {
 //      -0.5f*500, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
	//	0.5f * 500, -0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
	//	0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
	//	0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
	//	-0.5f * 500,  0.5f * 500, 0.5f * 500, 1.0f, 0.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500, 0.5f * 500, 1.0f, 0.0f,0.0f,
	//	
	//    -0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,//Back
	//	 0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//	 0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//	 0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//    -0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//    -0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//	
	//	 0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  -0.5f * 500, 0.5f * 500, 0.0f, 0.0f,1.0f,
 //     
	//	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
	//	
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f,1.0f,
	//	0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,1.0f,
	//	0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f,1.0f,
	//	0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f,1.0f,
	//	-0.5f * 500, -0.5f * 500,  0.5f * 500, 0.0f, 1.0f,1.0f,
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f,1.0f,
	//	
	//	-0.5f * 500,  0.5f * 500, -0.5f * 500, 1.0f, 0.2f,0.5f,
	//	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 0.2f,0.5f,
	//	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f,0.5f,
	//	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f,0.5f,
	//	-0.5f * 500,  0.5f * 500,  0.5f * 500, 1.0f, 0.2f,0.5f,
	//	-0.5f * 500,  0.5f * 500, -0.5f * 500, 1.0f, 0.2f,0.5f,
	//};


	// use with Perspective Projection
	float vertices[] = {
		/*CUBO1 -> white body/eyes */
		-0.5f, -0.5f, 0.5f,		0.7852f, 0.7930f, 0.8945f,//Front
		 0.5f, -0.5f, 0.5f,		0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f, 0.5f,		0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f, 0.5f,		0.7852f, 0.7930f, 0.8945f,
		-0.5f,  0.5f, 0.5f,		0.7852f, 0.7930f, 0.8945f,
		-0.5f, -0.5f, 0.5f,		0.7852f, 0.7930f, 0.8945f,

		-0.5f, -0.5f,-0.5f,		0.7852f, 0.7930f, 0.8945f,//Back
		 0.5f, -0.5f,-0.5f,		0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f,-0.5f,		0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f,-0.5f,		0.7852f, 0.7930f, 0.8945f,
		-0.5f,  0.5f,-0.5f,		0.7852f, 0.7930f, 0.8945f,
		-0.5f, -0.5f,-0.5f,		0.7852f, 0.7930f, 0.8945f,

		 0.5f, -0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,//Right 
		 0.5f, -0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f,  -0.5f, 0.5f,	0.7852f, 0.7930f, 0.8945f,
								
		-0.5f,  0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,//Left
		-0.5f,  0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f, -0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f, -0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f, -0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f,  0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
								
		-0.5f, -0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,//Bottom
		 0.5f, -0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f, -0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f, -0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f, -0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f, -0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
								
		-0.5f,  0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,//Up
		 0.5f,  0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		 0.5f,  0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f,  0.5f,  0.5f,	0.7852f, 0.7930f, 0.8945f,
		-0.5f,  0.5f, -0.5f,	0.7852f, 0.7930f, 0.8945f,

		/*CUBO2 -> Blue face */
		-0.5f, -0.5f, 0.5f,		0.4102f, 0.8047f, 0.9219f,//Front
		 0.5f, -0.5f, 0.5f,		0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f, 0.5f,		0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f, 0.5f,		0.4102f, 0.8047f, 0.9219f,
		-0.5f,  0.5f, 0.5f,		0.4102f, 0.8047f, 0.9219f,
		-0.5f, -0.5f, 0.5f,		0.4102f, 0.8047f, 0.9219f,
								
		-0.5f, -0.5f,-0.5f,		0.4102f, 0.8047f, 0.9219f,//Back
		 0.5f, -0.5f,-0.5f,		0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f,-0.5f,		0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f,-0.5f,		0.4102f, 0.8047f, 0.9219f,
		-0.5f,  0.5f,-0.5f,		0.4102f, 0.8047f, 0.9219f,
		-0.5f, -0.5f,-0.5f,		0.4102f, 0.8047f, 0.9219f,
								
		 0.5f, -0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,//Right 
		 0.5f, -0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f,  -0.5f, 0.5f,	0.4102f, 0.8047f, 0.9219f,
								
		-0.5f,  0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,//Left
		-0.5f,  0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f, -0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f, -0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f, -0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f,  0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
								
		-0.5f, -0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,//Bottom
		 0.5f, -0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f, -0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f, -0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f, -0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f, -0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
								
		-0.5f,  0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,//Up
		 0.5f,  0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		 0.5f,  0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f,  0.5f,  0.5f,	0.4102f, 0.8047f, 0.9219f,
		-0.5f,  0.5f, -0.5f,	0.4102f, 0.8047f, 0.9219f,

		/*CUBO3 -> Blue hair */
		-0.5f, -0.5f, 0.5f,		0.1016f, 0.3242f, 0.6953f,//Front
		 0.5f, -0.5f, 0.5f,		0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f, 0.5f,		0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f, 0.5f,		0.1016f, 0.3242f, 0.6953f,
		-0.5f,  0.5f, 0.5f,		0.1016f, 0.3242f, 0.6953f,
		-0.5f, -0.5f, 0.5f,		0.1016f, 0.3242f, 0.6953f,
								
		-0.5f, -0.5f,-0.5f,		0.1016f, 0.3242f, 0.6953f,//Back
		 0.5f, -0.5f,-0.5f,		0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f,-0.5f,		0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f,-0.5f,		0.1016f, 0.3242f, 0.6953f,
		-0.5f,  0.5f,-0.5f,		0.1016f, 0.3242f, 0.6953f,
		-0.5f, -0.5f,-0.5f,		0.1016f, 0.3242f, 0.6953f,
								
		 0.5f, -0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,//Right 
		 0.5f, -0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f,  -0.5f, 0.5f,	0.1016f, 0.3242f, 0.6953f,
								
		-0.5f,  0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,//Left
		-0.5f,  0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f, -0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f, -0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f, -0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f,  0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
								
		-0.5f, -0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,//Bottom
		 0.5f, -0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f, -0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f, -0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f, -0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f, -0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
								
		-0.5f,  0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,//Up
		 0.5f,  0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		 0.5f,  0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f,  0.5f,  0.5f,	0.1016f, 0.3242f, 0.6953f,
		-0.5f,  0.5f, -0.5f,	0.1016f, 0.3242f, 0.6953f,

		/*CUBO4 -> Violet glasses */
		-0.5f, -0.5f, 0.5f,		0.2461f, 0.1563f, 0.3203f,//Front
		 0.5f, -0.5f, 0.5f,		0.2461f, 0.1563f, 0.3203f,
		 0.5f,  0.5f, 0.5f,		0.2461f, 0.1563f, 0.3203f,
		 0.5f,  0.5f, 0.5f,		0.2461f, 0.1563f, 0.3203f,
		-0.5f,  0.5f, 0.5f,		0.2461f, 0.1563f, 0.3203f,
		-0.5f, -0.5f, 0.5f,		0.2461f, 0.1563f, 0.3203f,
								
		-0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,//Back
		 0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f,  0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f,  0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f,  0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
								
		 0.5f, -0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,//Right 
		 0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f,  0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f,  0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f,  0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f, -0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,
								
		-0.5f,  0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,//Left
		-0.5f,  0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f, -0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f,  0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,
								
		-0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,//Bottom
		 0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f, -0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,
		 0.5f, -0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f, -0.5f,  0.5f,	0.2461f, 0.1563f, 0.3203f,
		-0.5f, -0.5f, -0.5f,	0.2461f, 0.1563f, 0.3203f,
								
		-0.5f, 0.5f, -0.5f,		0.2461f, 0.1563f, 0.3203f,//Up
		 0.5f, 0.5f, -0.5f,		0.2461f, 0.1563f, 0.3203f,
		 0.5f, 0.5f,  0.5f,		0.2461f, 0.1563f, 0.3203f,
		 0.5f, 0.5f,  0.5f,		0.2461f, 0.1563f, 0.3203f,
		-0.5f, 0.5f,  0.5f,		0.2461f, 0.1563f, 0.3203f,
		-0.5f, 0.5f, -0.5f,		0.2461f, 0.1563f, 0.3203f,
	};

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f, 0.0f, -35.0f),
		glm::vec3( 5.0f, 0.0f, -35.0f),
		glm::vec3(-5.0f, 0.0f, -35.0f),
		glm::vec3( 0.0f, 8.0f, -35.0f),
		glm::vec3( 3.0f, 9.0f, -30.0f),
		glm::vec3(-3.0f, 9.0f, -30.0f), //[5]
		glm::vec3( 3.0f, 9.0f,-29.99f),
		glm::vec3(-3.0f, 9.0f,-29.99f),
		glm::vec3( 2.5f, 8.5f,-29.98f),
		glm::vec3(-2.5f, 8.5f,-29.98f),
		glm::vec3( 0.0f, 9.0f, -30.0f), //[10]
		glm::vec3( 0.0f,13.0f, -35.0f),
		glm::vec3( 6.0f, 8.0f, -35.0f),
		glm::vec3(-6.0f, 8.0f, -35.0f),
		glm::vec3( 0.0f,-5.0f, -35.0f),
		glm::vec3( 2.0f,-8.0f, -35.0f), //[15]
		glm::vec3(-2.0f,-8.0f, -35.0f),
		glm::vec3( 5.0f,-3.5f, -35.0f),
		glm::vec3(-5.0f,-3.5f, -35.0f),
		glm::vec3( 0.0f, 9.0f, -41.5f)
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. Despues colocamos las caracteristicas de los vertices
	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		//model = glm::rotate(model, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(1.0f,1.0f,-1.0f));
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate( model, 0.5f, glm::vec3( 1.0f, 0.0f, 0.0f ) ); // use to compare orthographic and perspective projection
		//view = glm::translate( view, glm::vec3( screenWidth / 2, screenHeight / 2,-700.0f ) ); // use with orthographic projection

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);

		
		//Las transformaciones geometricas se hacen en orden de pila (de abajo a arriba)
		//FIG1, cubo del tronco de TRISTEZA
	    model = glm::mat4(1.0f); //después de dibujar resetea la pos. al origen; limpia el estado de la matriz
		model = glm::translate(model, cubePositions[0]); //cubePositions[] trae a los vectores declarados arriba en el vector
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));   
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//FIG2, cubo del brazo derecho de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[1]);
		model = glm::scale(model, glm::vec3(2.0f, 6.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//FIG3, cubo del brazo izquierdo de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[2]);
		model = glm::scale(model, glm::vec3(2.0f, 6.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//FIG4, cubo de la cabeza de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[3]);
		model = glm::scale(model, glm::vec3(10.0f, 8.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		//FIG5, cubo de circulo lentes der de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[4]);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		//FIG6, cubo de circulo lentes izq de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[5]);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		//FIG7, cubo de ojo der de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[6]);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//FIG8, cubo de ojo izq de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[7]);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//FIG9, cubo de retina der de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[8]);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//FIG10, cubo de retina izq de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[9]);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//FIG11, cubo de centro lentes de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[10]);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		//FIG12, cubo de cabello sup de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[11]);
		model = glm::scale(model, glm::vec3(14.0f, 2.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//FIG13, cubo de cabello lateral der de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[12]);
		model = glm::scale(model, glm::vec3(2.0f, 8.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//FIG14, cubo de cabello lateral izq de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[13]);
		model = glm::scale(model, glm::vec3(2.0f, 8.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//FIG15, cubo cadera de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[14]);
		model = glm::scale(model, glm::vec3(8.0f, 2.0f, 8.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//FIG16, cubo de pierna der de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[15]);
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		//FIG17, cubo de pierna izq de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[16]);
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		//FIG18, cubo de mano der de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[17]);
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		//FIG19, cubo de mano izq de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[18]);
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);
		
		//FIG20, cubo de cabello parte trasera de TRISTEZA
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[19]);
		model = glm::scale(model, glm::vec3(14.0f, 10.0f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.4f;
 }


