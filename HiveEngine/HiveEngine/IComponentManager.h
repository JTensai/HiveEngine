#pragma once

#include <glm/glm.hpp>

class IComponentManager {
public:
	//virtual bool isKeyDown(int key) { return false; }
	virtual void update(float delta) {}
	virtual void draw() {}

};