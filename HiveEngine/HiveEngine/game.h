#pragma once

#define HE_GAMESTATE_NORMAL 0
#define HE_GAMESTATE_CLOSING 1

#include <iostream>
#include <fstream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tinyxml2/tinyxml2.h>

#include "tempmodel.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "UIManager.h"
#include "GameWorld.h"
#include "Graphics.h"

using namespace std;

namespace Hive
{
	const float TIMESTEP = 1.0f / 60.0f;

	enum class Gamestate
	{
		NORMAL,
		CLOSING
	};

	GLuint LoadShader(const char* vertex_file_path, const char* fragment_file_path);

	class Game {
	private:
		glm::vec3 camera_position;
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 world_matrix;
		glm::mat4 world_view_projection;
		char* core_xml_filename;
		char* game_xml_filename;
		char* map_xml_filename;
		GLuint shader_program_id;
		GLuint vertex_array_id;
		GLFWwindow* glfw_window;
		InputManager* input_manager;
		float timestep_delta;
		bool update_cache_swap_flag;
		int player_unit_handle;
		int player_actor_handle;
		int world_cursor_actor_handle;

	public:
		Game();
		~Game() {}

		//Initialize
		//Called after GLFW initialization but before OpenGL context creation and GLEW initialization.
		void initialize(char* core_xml_filename, char* game_xml_filename, char* map_xml_filename);

		//Load
		//Called after initialization of OpenGL context before entering game loop.
		void load(GLFWwindow* window);

		//Update
		//Called during game loop, passed amount of time in seconds since last loop.
		//Returns game state: HE_GAMESTATE_NORMAL, HE_GAMESTATE_CLOSING
		Gamestate update(float delta);

		//Draw
		//Called during game loop after update.
		void draw();

		//Close
		//Called after the game loop has been exited, before program termination.
		void close();
	};

}

