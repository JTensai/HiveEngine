#define TINYOBJLOADER_IMPLEMENTATION
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s << std::endl;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tinyxml2/tinyxml2.h>
#include <tiny_obj_loader.h>

#include <iostream>
#include <stdio.h>

#include "tempmodel.h"
#include "game.h"
#include "InputManager.h"
////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	double lastTime = 0;
	Game game;
	
	if (!glfwInit())
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	game.initialize(argv[1]);

	GLFWwindow* window; // (In the accompanying source code, this variable is global)
	window = glfwCreateWindow(1024, 768, "Hive Engine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");
		glfwTerminate();
		return -1;
	}

	//InputManager::getInstance()->setKeyCallbackForWindow(window);//set up the key input

	glfwMakeContextCurrent(window); // Initialize GLEW

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	game.load(window);

	while(true) {
		double time = glfwGetTime();

		if (game.update((float)(time - lastTime))) {
			//If update returns a non-zero value begin closing the program
			break;
		}
		lastTime = time;

		game.draw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	game.close();

	glfwTerminate();

	return 0;
}