#include "UIElement.h"

using namespace Hive;

UIElement::UIElement()
{
}

UIElement::UIElement(glm::vec2 bottom_left, float width, float height, DTextureHandle texture_handle)
{
	this->bottom_left = bottom_left;
	this->width = width;
	this->height = height;
	this->z_index = 0;
	this->rotation = 0;
	this->texture_handle = texture_handle;
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
