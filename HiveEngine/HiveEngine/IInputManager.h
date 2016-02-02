#pragma once

#include <glm/glm.hpp>

class IInputManager {
public:
	virtual bool isKeyDown(int key) { return false; }
	virtual glm::vec2 getMousePosition() { return glm::vec2(0); }
	virtual bool isMouseDown(int button) { return false; }
	virtual void registerMouseCallback(int button, void(*callback)()) {}
	virtual void registerKeyCallback(int key, void(*callback)()) {}
};