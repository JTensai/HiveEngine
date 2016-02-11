#pragma once

#include <glm/glm.hpp>

class IInputManager {
public:
	virtual bool isKeyDown(int key) = 0;
	virtual glm::vec2 getMousePosition() = 0;
	virtual bool isMouseDown(int button) = 0;
	virtual void registerMouseCallback(int button, void(*callback)()) = 0;
	virtual void registerKeyCallback(int key, void(*callback)()) = 0;
};