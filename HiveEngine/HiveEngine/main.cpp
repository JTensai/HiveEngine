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

#include "game.h"
////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	try
	{
		double lastTime = 0;
		Hive::Game game;

		fprintf(stdout, "Initializing GLFW...\n");
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			return -1;
		}
		fprintf(stdout, "Finished initializing GLFW.\n");

		fprintf(stdout, "Initializing game...\n");
		game.initialize(argv[1]);
		fprintf(stdout, "Finished initializing game.\n");

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

		fprintf(stdout, "Loading game...\n");
		game.load(window);
		fprintf(stdout, "Finished loading game.\n");

		fprintf(stdout, "Entering game loop...\n");
		Hive::Gamestate gs = Hive::Gamestate::NORMAL;
		while (gs != Hive::Gamestate::CLOSING) {
			double time = glfwGetTime();

			gs = game.update((float)(time - lastTime));
			lastTime = time;
			if (gs != Hive::Gamestate::CLOSING)
			{
				game.draw();

				// Swap buffers
				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		}
		fprintf(stdout, "Exiting game loop.\n");

		fprintf(stdout, "Closing game...\n");
		game.close();
		fprintf(stdout, "Finished closing game.\n");

		glfwTerminate();

		fprintf(stdout, "Execution complete.\n");
		return 0;
	}
	catch(...)
	{
		std::cerr << "Unkown exception excountered.\n";
		std::system("PAUSE");
		return 1;
	}
}