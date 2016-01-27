#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "IInputManager.h"

class InputManager : public IInputManager
{
private:
	glm::vec3 _cameraPosition = glm::vec3(3, .5, 0);
	GLFWwindow* _window;

public:
	InputManager(GLFWwindow* window);
	~InputManager();
	bool isKeyDown(int key) override;
	glm::vec2 getMousePosition() override;
	bool isMouseDown(int button) override;
	void registerMouseCallback(int button, void(*callback)()) override;
	void registerKeyCallback(int key, void(*callback)()) override;
};

