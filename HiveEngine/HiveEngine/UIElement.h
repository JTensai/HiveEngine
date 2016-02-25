#pragma once
#include <glm/glm.hpp>

class UIElement
{
public:
	UIElement();
	UIElement(glm::vec2 top_left, float width, float height, int z_index);
	~UIElement();
	void update(float delta);
	void draw();

//private:
	glm::vec2 top_left = glm::vec2();
	float width;
	float height;
	int z_index;
	// texture to display
	// type of element
	// each sub element will define its own extra methods that interact with the mouse
};

