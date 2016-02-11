#include "InputManager.h"

namespace Hive
{

	InputManager::InputManager(GLFWwindow* window) {
		_window = window;
	}
	InputManager::~InputManager() {

	}

	bool InputManager::isKeyDown(int key) {
		return glfwGetKey(_window, key) == GLFW_PRESS;
	};
	glm::vec2 InputManager::getMousePosition() {
		return glm::vec2(0);
	};
	bool InputManager::isMouseDown(int button) {
		return false;
	};
	void InputManager::registerMouseCallback(int button, void(*callback)()) {

	};
	void InputManager::registerKeyCallback(int key, void(*callback)()) {

	};

}