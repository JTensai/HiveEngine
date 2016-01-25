#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager
{
private:
	glm::vec3 _cameraPosition = glm::vec3(3, .5, 0);

	InputManager();

public:
	static InputManager* instance;

	static InputManager* getInstance()
	{
		if (!instance)
		{
			instance = new InputManager();
		}
		return instance;
	}
	~InputManager();

	void setKeyCallbackForWindow(GLFWwindow* window);

	//static key_callback
	//set as a callback method for keyboard input during load, forwards the callback to a non-static function
	//so that it can access member variables
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		getInstance()->key_callbackImpl(window, key, scancode, action, mods);
	}

	//non-static key_callback
	//receives and handles the key events from the static key_callback
	void key_callbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods);

	glm::vec3 getCameraPosition();

	glm::vec3 getCameraLookAtPosition();
};

