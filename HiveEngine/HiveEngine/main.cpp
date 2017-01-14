#define TINYOBJLOADER_IMPLEMENTATION
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tinyxml2/tinyxml2.h>
#include <tiny_obj_loader.h>
#include <IL\il.h>
#include <IL\ilu.h>

#include "game.h"
#include "Asset.h"
#include "Exceptions.h"

bool file_valid(const char* filename)
{
	ifstream file(filename);
	if (file.good())
	{
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	char* core_xml_filename = "resources/core.xml";
	char* game_xml_filename = "resources/game.xml";
	char* map_xml_filename = "resources/map.xml";

	if (argc > 1)
	{
		core_xml_filename = argv[1];
		if (argc > 2)
		{
			game_xml_filename = argv[2];
			if (argc > 3)
			{
				map_xml_filename = argv[3];
			}
		}
	}

	fprintf(stdout, "Loading from:\n\tCore: %s\n\tGame: %s\n\tMap: %s\n", core_xml_filename, game_xml_filename, map_xml_filename);

	if (!file_valid(core_xml_filename))
	{
		fprintf(stderr, "Unable to open core xml file %s, can not continue.", core_xml_filename);
		std::system("PAUSE");
		return 12;
	}
	if (!file_valid(game_xml_filename))
	{
		fprintf(stderr, "Unable to open game xml file %s, can not continue.", game_xml_filename);
		std::system("PAUSE");
		return 13;
	}
	if (!file_valid(map_xml_filename))
	{
		fprintf(stderr, "Unable to open map xml file %s, can not continue.", map_xml_filename);
		std::system("PAUSE");
		return 14;
	}


	GLFWwindow* window = nullptr; // (In the accompanying source code, this variable is global)
	try
	{
		double lastTime = 0;
		Hive::Game game;

		fprintf(stdout, "Initializing GLFW...\n");
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			std::system("PAUSE");
			return 1;
		}
		fprintf(stdout, "Finished initializing GLFW.\n");

		fprintf(stdout, "Initializing IL\\ILU...\n");
		ilInit();
		if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
		{
			printf("DevIL version mismatch ...exiting!\n");
			std::system("PAUSE");
			return 2;
		}
		fprintf(stdout, "Finished initializing IL\\ILU.\n");
		
		fprintf(stdout, "Initializing game...\n");
		game.initialize(core_xml_filename, game_xml_filename, map_xml_filename);
		fprintf(stdout, "Finished initializing game.\n");

		window = glfwCreateWindow(1024, 768, "Hive Engine", NULL, NULL);
		if (window == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");
			glfwTerminate();
			std::system("PAUSE");
			return 3;
		}

		//InputManager::getInstance()->setKeyCallbackForWindow(window);//set up the key input

		glfwMakeContextCurrent(window); // Initialize GLEW

		glewExperimental = true; // Needed in core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			std::system("PAUSE");
			return 4;
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
		fprintf(stdout, "Exiting game loop...\n");

		fprintf(stdout, "Closing game...\n");
		game.close();
		fprintf(stdout, "Finished closing game.\n");

		glfwTerminate();

		fprintf(stdout, "Execution complete.\n");
	}
	catch (const Hive::AssetLoadException& e)
	{
		glfwTerminate();
		fprintf(stderr, "Asset Load Exception: %s\n", e.msg.c_str());
		std::system("PAUSE");
		return 5;
	}
	catch (const Hive::DataErrorException& e)
	{
		glfwTerminate();
		fprintf(stderr, "Data Error Exception: %s\n", e.msg.c_str());
		std::system("PAUSE");
		return 6;
	}
	catch (const Hive::EffectException& e)
	{
		glfwTerminate();
		fprintf(stderr, "Effect Error Exception: %s\n", e.msg.c_str());
		std::system("PAUSE");
		return 7;
	}
	catch (const Hive::EffectTreeException& e)
	{
		glfwTerminate();
		fprintf(stderr, "Effect Tree Exception: %s\n", e.msg.c_str());
		std::system("PAUSE");
		return 8;
	}
	catch (const Hive::UnimplementedException& e)
	{
		glfwTerminate();
		fprintf(stderr, "Unimplemented Exception: %s\n", e.msg.c_str());
		std::system("PAUSE");
		return 9;
	}
	catch (const Hive::Exception& e)
	{
		glfwTerminate();
		fprintf(stderr, "Exception: %s\n", e.msg.c_str());
		std::system("PAUSE");
		return 10;
	}
	catch(const std::exception& e)
	{
		glfwTerminate();
		fprintf(stderr, "Unkown exception excountered: %s\n", e.what());
		std::system("PAUSE");
		return 11;
	}

#ifdef _DEBUG
	std::system("PAUSE");
#endif // DEBUG
	return 0;
}