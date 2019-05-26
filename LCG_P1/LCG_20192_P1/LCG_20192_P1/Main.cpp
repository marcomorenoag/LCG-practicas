//Marco Antonio Moreno Guerra
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

GLuint shaderProgram, shaderProgramGreen; // Se vuelven globales para poder usarlos

// Shaders
const GLchar* vertexShaderSource = 
{
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0" 
};
const GLchar* fragmentShaderSource = 
{
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(0.45f, 0.6f, 0.3f, 1.0f);\n"
	"}\n\0"
};

const GLchar* fragmentShaderSourceGreen =
{
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\n\0"
};

// Funciones de configuracion del shader

void CrearShader(void);




int main() {
	glfwInit(); //Manejador de ventana
	//Verificaci�n de compatibilidad 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "MARCO ANTONIO MORENO GUERRA", nullptr, nullptr);
	
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

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	CrearShader();

	// Set up vertex data (and buffer(s)) and attribute pointers
	// Vertices en 3 dimensiones, se mete este arreglo de vertices en un buffer
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // Left
		0.5f, -0.5f, 0.0f, // Right
		0.0f,  0.5f, 0.0f,  // Top
		-0.5f, 0.65f, 0.0f, // 4to vertice
		-1.0f, 1.0f, 0.0f,
		-0.5f, 0.0f, 0.0f
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	


	// Este while es un ciclo de dibujo infinito hasta que se desee cerrar la ventana
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents(); // Funci�n que cacha los eventos del teclado

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.2f, 0.9f, 1.0f); // Asigna un color de fondo: se usa RGB (rango 0-1) + transparencia
		glClear(GL_COLOR_BUFFER_BIT); 


		// Draw our first triangle

		glBindVertexArray(VAO);
		glPointSize(5.0); //indica la cantidad de pixeles que ocupar�n los puntos
		//SINTATIX: glDrawArrays(MODO_DIBUJO, #Elemento, CantidadElementos);
		//glDrawArrays(GL_POINTS, 0, 3); // Funci�n que se encarga de dibujar los tres vertices del arreglo iniciando desde el VERTICE 0 hasta el 3 y c�mo debe considerarlos
		//glDrawArrays(GL_LINES, 0, 4);
		//glDrawArrays(GL_LINES_LOOP, 0, 4); //Cierra la figura con los vertices
		//glDrawArrays(GL_LINES_STRIP, 0, 4); 
		//glDrawArrays(GL_LINES_LOOP, 0, 3);
		//glDrawArrays(GL_POINTS, 3, 1);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgramGreen);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glBindVertexArray(0); 

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void CrearShader()
{
    // Creamos el vertex shader y guardamos su identificador
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	// Verificamos los errores en tiempo de ejecuci�n
	GLint success;
	GLchar infoLog[512];


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// Creamos el fragment shader y guardamos su identificador
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Creamos el fragment shader y guardamos su identificador
	// Fragment shader Green
	GLuint fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderGreen, 1, &fragmentShaderSourceGreen, NULL);
	glCompileShader(fragmentShaderGreen);

	// Verificamos los errores en tiempo de ejecuci�n

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Creamos un nuevo programa y se asignamos
	// sus correspondientes vertex y fragment shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//glUseProgram(shaderProgram);

	// Creamos un nuevo programa y se asigna
	// sus correspondientes vertex y fragment shaders
	shaderProgramGreen = glCreateProgram();
	glAttachShader(shaderProgramGreen, vertexShader);
	glAttachShader(shaderProgramGreen, fragmentShaderGreen);
	glLinkProgram(shaderProgramGreen);
	//glUseProgram(shaderProgram);

	// Verificamos que no hay error en el programa
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}

