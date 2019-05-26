#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", nullptr, nullptr);
	
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

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	//Se encarga de concatenar los dos archivos (vertices y fragmentos)
	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//Posición			  //Color
		/*0.0f,  0.5f, 0.0f,    1.0f,0.0f,0.0f,  // top right
		0.5f, -0.5f, 0.0f,    0.0f,1.0f,0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f,0.0f,1.0f // top left */

		/*FIG1: Cuadrado cuadrante2*/
		-0.8f, 0.2f, 0.0f,		0.0f, 1.0f, 1.0f,
		-0.8f, 0.6f, 0.0f,		0.0f, 1.0f, 1.0f,
		-0.4f, 0.6f, 0.0f,		0.0f, 1.0f, 1.0f,
		-0.4f, 0.2f, 0.0f,		0.0f, 1.0f, 1.0f,
		
		/*FIG2: Triangulo cuadrante1*/
		0.2f, 0.2f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.4f, 0.6f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.6f, 0.2f, 0.0f,		1.0f, 0.0f, 0.0f,

		/*FIG3: Rectangulo cuadrante4*/
		0.8f, -0.3f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.8f, -0.6f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.2f, -0.6f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.2f, -0.3f, 0.0f,		0.0f, 1.0f, 0.0f,

		/*FIG4: Pentagono cuadrante3*/
		-0.5f, -0.2f, 0.0f,		0.0f, 0.0f, 1.0f,
		-0.2f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
		-0.35f, -0.8f, 0.0f,	0.0f, 0.0f, 1.0f,
		-0.65f, -0.8f, 0.0f,	0.0f, 0.0f, 1.0f,
		-0.8f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f

	};
	//indices de los vertices para saber orden de dibujo
	unsigned int indices[] = {  // note that we start from 0!
		//2,0,1  // first Triangle
		//2,3,0,1 //cuadrado
		//1, 2, 3   // second Triangle
		0, 1, 2, 3,			//Cuadrado
		4, 5, 6,			//Triangulo
		7, 8, 9, 10,		//Rectangulo
		11, 12, 13, 14, 15	//Pentagono
	};
	



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO); //Genera el arreglo de vertices (se lo pasa)
	glGenBuffers(1, &VBO);		//Crea Vertex Buffer Object
	glGenBuffers(1, &EBO);		//Element Buffer Object

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO); 

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //modo de dibujo estático

	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices
	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	//3 es el numero de vertices que lee
	glEnableVertexAttribArray(0);

	//Color
	//Lee la localidad 1, manda 6 coordenadas (pos,color)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Enlaza el buffer


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents(); //Atrapa errores

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Pinta el color del fondo RGB
		//Si el triangulo es blanco la GPU es integrada, si es negro la GPU es independiente
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		//Manda a llamar y ensambla los shaders usados
		ourShader.Use();
		//Unión del VAO Vertex Array Object
		glBindVertexArray(VAO);
		
		//Dibujado de elementos
		//glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 1);
		//El 0 va forzosamente; el ultimo parametro indica cual será el indice de inicio de dibujo del unsigned int indices[]

		/*FIG1: Cuadrado cuadrante2*/
		glDrawElementsBaseVertex(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0, 0);

		/*FIG2: Triangulo cuadrante1*/
		glDrawElementsBaseVertex(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0, 4);

		/*FIG3: Rectangulo cuadrante4*/
		glDrawElementsBaseVertex(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0, 7);

		/*FIG4: Pentagono cuadrante3*/
		glDrawElementsBaseVertex(GL_LINE_LOOP, 5, GL_UNSIGNED_INT, 0, 11);

		

		//Modo de dibujo TRIANGULO, No signados, solo 3 vertices; 0,0 -> indica el inicio y fin
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

