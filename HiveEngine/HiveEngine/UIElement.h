#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

class UIElement
{
public:
	UIElement();
	UIElement(glm::vec2 bottom_left, float width, float height, Hive::Texture texture);
	~UIElement();
	void update(float delta);
	void draw();

//private:
	glm::vec2 bottom_left = glm::vec2();
	float width;
	float height;
	float rotation;
	int z_index;
	Hive::Texture texture = Hive::Texture("resources/missing_image.jpg", new Hive::DTexture()); // texture to display
	Hive::DTexture* data = new Hive::DTexture();
	// type of element
	// each sub element will define its own extra methods that interact with the mouse
};

