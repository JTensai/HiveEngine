#pragma once

#define HE_GAMESTATE_NORMAL 0
#define HE_GAMESTATE_CLOSING 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tinyxml2/tinyxml2.h>

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "tempmodel.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "UIManager.h"
#include "GameWorld.h"

using namespace std;

namespace Hive
{
	const float TIMESTEP = 1.0f / 60.0f;
	const glm::vec3 BG = glm::vec3(0.6f, 0.6f, 0.9f);
	const glm::vec3 SUB_FLOOR = glm::vec3(0.25f, 0.2f, 0.2f);
	const glm::vec3 FLOOR = glm::vec3(0.2f, 0.15f, 0.15f);
	const glm::vec3 WALL_BASE = glm::vec3(0.175f, 0.125f, 0.125f);
	const glm::vec3 WALL_TOP = glm::vec3(0.02f, 0.015f, 0.015f);

	enum class Gamestate
	{
		NORMAL,
		CLOSING
	};

	GLuint LoadShader(const char* vertex_file_path, const char* fragment_file_path);

	class Game {
	private:
		glm::vec3 light_direction;
		glm::vec4 light_color;
		glm::vec3 ambient_color;
		glm::vec3 camera_position;
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 world_matrix;
		glm::mat4 world_view_projection;
		TempModel* temp_model = 0;
		char* xml_filename;
		GLuint shader_program_id;
		GLuint shader_matrix_id;
		GLuint shader_view_matrix_id;
		GLuint shader_world_matrix_id;
		GLuint vertex_array_id;
		GLFWwindow* glfw_window;
		InputManager* input_manager;
		float camera_rotation = 0;
		float timestep_delta;
		bool update_cache_swap_flag;

	public:
		Game();
		~Game() {}

		//Initialize
		//Called after GLFW initialization but before OpenGL context creation and GLEW initialization.
		void initialize(char* xmlFilename);

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

