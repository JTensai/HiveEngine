#include "InputManager.h"

InputManager* InputManager::instance;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
	delete instance;
}

void InputManager::setKeyCallbackForWindow(GLFWwindow* window)
{
	glfwSetKeyCallback(window, key_callback);
}

void InputManager::key_callbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_W:
		_cameraPosition.x -= .2f;
		break;
	case GLFW_KEY_A:
		_cameraPosition.z += .2f;
		break;
	case GLFW_KEY_S:
		_cameraPosition.x += .2f;
		break;
	case GLFW_KEY_D:
		_cameraPosition.z -= .2f;
		break;
	default:
		break;
	}
}

glm::vec3 InputManager::getCameraPosition()
{
	return _cameraPosition;
}

glm::vec3 InputManager::getCameraLookAtPosition()
{
	return glm::vec3(_cameraPosition.x-1,_cameraPosition.y,_cameraPosition.z);
}