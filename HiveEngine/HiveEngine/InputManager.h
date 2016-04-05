#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "IInputManager.h"
#include "Exceptions.h"

namespace Hive
{

	class InputManager : public IInputManager
	{
	private:
		glm::vec3 camera_position = glm::vec3(3, .5, 0);
		GLFWwindow* window;
		glm::mat4 projection_i;
		glm::mat4 view_i;
		float near_z;

		static InputManager* instance;
		static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
		void callback(GLFWwindow* window, int button, int action, int mods);

		std::vector<std::function<void()>> left_mouse_callbacks;
		std::vector<std::function<void()>> right_mouse_callbacks;

	public:
		InputManager(GLFWwindow* window);
		~InputManager();

		void updateProjection(glm::mat4 projection, float near_z) override;
		void updateView(glm::mat4 view, glm::vec3 camera_position) override;

		bool isKeyDown(int key) override;
		glm::vec2 getMousePosition() override;
		glm::vec2 getMousePositionFraction() override;
		glm::vec2 getMousePositionWorld() override;
		bool isMouseDown(int button) override;
		void registerMouseCallback(int button, std::function<void()> callback) override;
		void registerKeyCallback(int key, std::function<void()> callback) override;
	};

}