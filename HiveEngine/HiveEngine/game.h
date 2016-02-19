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
#include "ComponentManager.h"
#include "DataManager.h"
#include "UIManager.h"

using namespace std;

namespace Hive
{

	GLuint LoadShader(const char* vertex_file_path, const char* fragment_file_path);

	class Game {
	private:
		glm::vec3 _camPos;
		glm::mat4 _mProjectionMatrix;
		glm::mat4 _mViewMatrix;
		glm::mat4 _mWorldMatrix;
		glm::mat4 _mWVP;
		TempModel* _mpModel = 0;
		char* _cpXMLFilename;
		GLuint _iProgramID;
		GLuint _iMatrixID;
		GLuint _iViewMatrixID;
		GLuint _iWorldMatrixID;
		GLuint _iVertexArrayID;
		GLFWwindow* _wpWindow;
		InputManager* _inputManager;
		float _fCamRotation = 0;


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
		int update(float delta);

		//Draw
		//Called during game loop after update.
		void draw();

		//Close
		//Called after the game loop has been exited, before program termination.
		void close();
	};

}