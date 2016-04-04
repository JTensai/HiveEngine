#include "UIElement.h"

using namespace Hive;

UIElement::UIElement()
{
}

UIElement::UIElement(glm::vec2 bottom_left, float width, float height, DMaterialHandle materialHandle)
{
	this->bottom_left = bottom_left;
	this->width = width;
	this->height = height;
	this->z_index = 0;
	this->rotation = 0;
	material = materialHandle;
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
