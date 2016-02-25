#include "UIElement.h"



UIElement::UIElement()
{
}

UIElement::UIElement(glm::vec2 top_left, float width, float height, int z_index)
{
	this->top_left = top_left;
	this->width = width;
	this->height = height;
	this->z_index = z_index;
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
