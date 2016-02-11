#pragma once
/*
 ***************************
 * Input Manager
 * The input manager is responsible for providing a unified interface whereby all other systems may gain access to user input, whether that means polling or registering callback functions.
 * It will be necessary for some systems, like UI, to consume some input so that it is not seen by later systems.
 ***************************
 */

#include <glm/glm.hpp>

class IInputManager {
public:
	virtual bool isKeyDown(int key) = 0;
	virtual glm::vec2 getMousePosition() = 0;
	virtual bool isMouseDown(int button) = 0;
	virtual void registerMouseCallback(int button, void(*callback)()) = 0;
	virtual void registerKeyCallback(int key, void(*callback)()) = 0;
};