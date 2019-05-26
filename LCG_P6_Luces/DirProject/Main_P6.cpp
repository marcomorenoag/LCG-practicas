#include <iostream>
#include <cmath>

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"


// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void Inputs(GLFWwindow *window);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

//Coordenadas
GLfloat horizontalLight1 = 0.0f;
GLfloat verticalLight1 = 0.0f;
GLfloat horizontalLight2 = 2.0f;
GLfloat verticalLight2 = -2.0f;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 2.0f);
glm::vec3 lightPos2(2.0f, -2.0f, 2.0f);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow( WIDTH, HEIGHT, "LCG_Reporte6_MAMG", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    
    // Build and compile our shader program
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    
    // First, set the container's VAO (and VBO)
    GLuint VBO, containerVAO;
    glGenVertexArrays( 1, &containerVAO );
    glGenBuffers( 1, &VBO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    glBindVertexArray( containerVAO );
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * )0 );
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );
    glBindVertexArray( 0 );
    
    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
    GLuint lightVAO;
    glGenVertexArrays( 1, &lightVAO );
    glBindVertexArray( lightVAO );
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * )0 ); // Note that we skip over the normal vectors
    glEnableVertexAttribArray( 0 );

	//Proyección en perspectiva
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( GLfloat )SCREEN_WIDTH / ( GLfloat )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
		//Check any keyboard for movement for the lights with the arrows on the keyboard (UP, DOWN, LEFT, RIGHT)
		Inputs(window);

		// Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime( );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );
        DoMovement( );
        
        // Clear the colorbuffer
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        
        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use( );
        GLint lightPosLoc = glGetUniformLocation( lightingShader.Program, "light.position" );
        GLint viewPosLoc = glGetUniformLocation( lightingShader.Program, "viewPos" );
		glUniform3f( lightPosLoc, horizontalLight1, verticalLight1, lightPos.z);
        glUniform3f( viewPosLoc, camera.GetPosition( ).x, camera.GetPosition( ).y, camera.GetPosition( ).z );


		// Set lights properties, define el color de la luz (USUALMENTE ES BLANCA PARA QUE NO ALTERE EL COLOR DE LOS MATERIALES)
		glm::vec3 lightColor;
		lightColor.r = 1.0f;
		lightColor.g = 1.0f;
		lightColor.b = 1.0f;

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence //INTENSIDAD DE LUZ
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence //INTENSIDAD DE LUZ

		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), ambientColor.r, ambientColor.g, ambientColor.b);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), diffuseColor.r, diffuseColor.g, diffuseColor.b);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f); //Reflector de la luz especular

		// Set material properties, DEFINEN EL COLOR DEL MATERIAL
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 0.5f, 0.31f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.0f, 1.0f, 1.0f); //LA COMPONENTE DIFUSA USUALMENTE DEFINE EL COLOR DEL MATERIAL
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 1.0f, 1.0f, 1.0f); // Specular doesn't have full effect on this object's material
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 30.0f); //es el rango




		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint lightPosLoc2 = glGetUniformLocation(lightingShader.Program, "light.position");
		GLint viewPosLoc2 = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(lightPosLoc2, horizontalLight2, verticalLight2, lightPos2.z);
		glUniform3f(viewPosLoc2, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		
		// Set lights properties, define el color de la luz (USUALMENTE ES BLANCA PARA QUE NO ALTERE EL COLOR DE LOS MATERIALES)
		glm::vec3 lightColor2;
		lightColor2.r = 1.0f;
		lightColor2.g = 1.0f;
		lightColor2.b = 1.0f;
		
		glm::vec3 diffuseColor2 = lightColor2 * glm::vec3(0.5f); // Decrease the influence //INTENSIDAD DE LUZ
		glm::vec3 ambientColor2 = diffuseColor2 * glm::vec3(0.2f); // Low influence //INTENSIDAD DE LUZ
		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), ambientColor2.r, ambientColor2.g, ambientColor2.b);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), diffuseColor2.r, diffuseColor2.g, diffuseColor2.b);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f); //Reflector de la luz especular
		
		// Set material properties, DEFINEN EL COLOR DEL MATERIAL
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 0.5f, 0.31f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.0f, 1.0f, 1.0f); //LA COMPONENTE DIFUSA USUALMENTE DEFINE EL COLOR DEL MATERIAL
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 1.0f, 1.0f, 1.0f); // Specular doesn't have full effect on this object's material
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 30.0f); //es el rango
		//////////////////////////////////////////////////////////////////////////////////////////////////////////



        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix( );

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation( lightingShader.Program, "model" );
        GLint viewLoc = glGetUniformLocation( lightingShader.Program, "view" );
        GLint projLoc = glGetUniformLocation( lightingShader.Program, "projection" );
        
        // Pass the matrices to the shader
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
		glBindVertexArray(containerVAO);


		//DECLARACIÓN DE PRIMER CUBO
        // Draw the container (using container's vertex attributes)
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        glDrawArrays( GL_TRIANGLES, 0,36 );
		
		//DECLARACIÓN DE SEGUNDO CUBO
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 0.0f, 0.31f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 0.0f, 0.0f); //LA COMPONENTE DIFUSA USUALMENTE DEFINE EL COLOR DEL MATERIAL
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.75f, 0.75f, 0.75f); // Specular doesn't have full effect on this object's material
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 75.0f); //es el rango

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//DECLARACIÓN DE TERCER CUBO
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 0.5f, 0.31f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.25f, 0.50f, 0.75f); //LA COMPONENTE DIFUSA USUALMENTE DEFINE EL COLOR DEL MATERIAL
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.25f, 0.25f, 0.25f); // Specular doesn't have full effect on this object's material
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 25.0f); //es el rango

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//DECLARACIÓN DE CUARTO CUBO
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 0.5f, 0.31f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.0f, 1.0f, 0.0f); //LA COMPONENTE DIFUSA USUALMENTE DEFINE EL COLOR DEL MATERIAL
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.10f, 0.10f, 0.10f); // Specular doesn't have full effect on this object's material
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 10.0f); //es el rango

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, -2.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glBindVertexArray(0);
        
        // Also draw the lamp object, again binding the appropriate shader
        lampShader.Use( );
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation( lampShader.Program, "model" );
        viewLoc = glGetUniformLocation( lampShader.Program, "view" );
        projLoc = glGetUniformLocation( lampShader.Program, "projection" );
        
		// Set matrices
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        model = glm::mat4(1.0f);
        model = glm::translate( model, glm::vec3(horizontalLight1, verticalLight1, 2.0f));
        model = glm::scale( model, glm::vec3( 0.2f ) ); // Make it a smaller cube
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        
        // Draw the light object (using light's vertex attributes)
        glBindVertexArray( lightVAO );
        glDrawArrays( GL_TRIANGLES, 0, 36 );



		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(horizontalLight2, verticalLight2, 2.0f));
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray( 0 );
       
        // Swap the screen buffers
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays( 1, &containerVAO );
    glDeleteVertexArrays( 1, &lightVAO );
    glDeleteBuffers( 1, &VBO );
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    
    return EXIT_SUCCESS;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

void Inputs(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		horizontalLight1 += 0.01f;
		horizontalLight2 += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		horizontalLight1 -= 0.01f;
		horizontalLight2 -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		verticalLight1 += 0.01f;
		verticalLight2 += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		verticalLight1 -= 0.01f;
		verticalLight2 -= 0.01f;
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Use cooresponding shader when setting uniforms/drawing objects
//lightingShader.Use();
//GLint lightPosLoc2 = glGetUniformLocation(lightingShader.Program, "light.position");
//GLint viewPosLoc2 = glGetUniformLocation(lightingShader.Program, "viewPos");
//glUniform3f(lightPosLoc2, horizontalLight2, verticalLight2, lightPos2.z);
//glUniform3f(viewPosLoc2, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
//
//// Set lights properties, define el color de la luz (USUALMENTE ES BLANCA PARA QUE NO ALTERE EL COLOR DE LOS MATERIALES)
//glm::vec3 lightColor2;
//lightColor2.r = 1.0f;
//lightColor2.g = 1.0f;
//lightColor2.b = 1.0f;
//
//glm::vec3 diffuseColor2 = lightColor2 * glm::vec3(0.5f); // Decrease the influence //INTENSIDAD DE LUZ
//glm::vec3 ambientColor2 = diffuseColor2 * glm::vec3(0.2f); // Low influence //INTENSIDAD DE LUZ
//
//glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), ambientColor2.r, ambientColor2.g, ambientColor2.b);
//glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), diffuseColor2.r, diffuseColor2.g, diffuseColor2.b);
//glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f); //Reflector de la luz especular
//
//// Set material properties, DEFINEN EL COLOR DEL MATERIAL
//glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 0.5f, 0.31f);
//glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.0f, 1.0f, 1.0f); //LA COMPONENTE DIFUSA USUALMENTE DEFINE EL COLOR DEL MATERIAL
//glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 1.0f, 1.0f, 1.0f); // Specular doesn't have full effect on this object's material
//glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 30.0f); //es el rango
////////////////////////////////////////////////////////////////////////////////////////////////////////////
