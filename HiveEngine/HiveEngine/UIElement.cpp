#include "UIElement.h"



UIElement::UIElement()
{
}

UIElement::UIElement(glm::vec2 bottom_left, float width, float height, Hive::Texture texture = Hive::Texture("resources/texture.jpg", new Hive::DTexture()))
{
	this->bottom_left = bottom_left;
	this->width = width;
	this->height = height;
	this->z_index = 0;
	this->rotation = 0;
	this->texture = texture;
}

void UIElement::update(float delta) 
{

}

void UIElement::draw()
{

}

UIElement::~UIElement()
{
}
