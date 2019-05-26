#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "MAMG, REPORTE 2", nullptr, nullptr);
	
	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informaci�n de OpenGL del sistema
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
		//V�rtices de triangulos
		-0.4f, -0.8f, 0.0f,		0.725f, 0.478f, 0.341f, //V�rtice Triangulo Base1
		-0.8f, -0.2f, 0.0f,		0.725f, 0.478f, 0.341f, //V�rtice Triangulo Base1 y 2
		 0.4f, -0.8f, 0.0f,		0.725f, 0.478f, 0.341f, //V�rtice Triangulo Base1 y 2
		 0.8f, -0.2f, 0.0f,		0.725f, 0.478f, 0.341f, //V�rtice Triangulo Base2
		 0.0f,  0.3f, 0.0f,		1.0f,	1.0f,	1.0f,	//V�rtice Triangulo bandera
		 0.0f,  0.5f, 0.0f,		1.0f,	1.0f,	1.0f,	//V�rtice Triangulo bandera
		 0.2f,  0.3f, 0.0f,		1.0f,	1.0f,	1.0f,	//V�rtice Triangulo bandera

		 //V�rtices de las l�neas
		 0.0f, -0.2f, 0.0f,		0.0f,	0.0f,	0.0f,	//V�rtice de l�neas de la base de bandera
		 0.0f, 0.5f, 0.0f,		0.0f,	0.0f,	0.0f,	//V�rtice de l�neas de la base de bandera
		 0.2f, 0.3f, 0.0f,		0.0f,	0.0f,	0.0f,	//V�rtice de l�neas de la base de bandera
		 0.0f, 0.3f, 0.0f,		0.0f,	0.0f,	0.0f	//V�rtice de l�neas de la base de bandera
	};
	
	//indices de los vertices para saber orden de dibujo
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10	//Tri�ngulos
	};
	
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO); //Genera el arreglo de vertices (se lo pasa)
	glGenBuffers(1, &VBO);		//Crea Vertex Buffer Object
	glGenBuffers(1, &EBO);		//Element Buffer Object

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO); 

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //modo de dibujo est�tico

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
		glClearColor(0.0f, 0.635f, 0.91f, 1.0f); //Pinta el color del fondo RGB
		//Si el triangulo es blanco la GPU es integrada, si es negro la GPU es independiente
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		//Manda a llamar y ensambla los shaders usados
		ourShader.Use();
		//Uni�n del VAO Vertex Array Object
		glBindVertexArray(VAO);
		
		//Dibujado de elementos
		//glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 1);
		//El 0 va forzosamente; el ultimo parametro indica cual ser� el indice de inicio de dibujo del unsigned int indices[]


		/*TRIANGULO BASE1*/
		glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 0);
		/*TRIANGULO BASE2*/
		glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 1);
		/*TRIANGULO BANDERA*/
		glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 4);
		/*BASE DE BANDERA*/		
		glDrawElementsBaseVertex(GL_LINES, 2, GL_UNSIGNED_INT, 0, 7);
		glDrawElementsBaseVertex(GL_LINES, 2, GL_UNSIGNED_INT, 0, 8);
		glDrawElementsBaseVertex(GL_LINES, 2, GL_UNSIGNED_INT, 0, 9);

		//Modo de dibujo TRIANGULO, No signados, solo 3 vertices; 0,0 -> indica el inicio y fin
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

