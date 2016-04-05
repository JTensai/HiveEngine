#include "UIElement.h"

using namespace Hive;

UIElement::UIElement()
{
}

UIElement::UIElement(DUIElementHandle handle) {
	DUIElement* element = DUIElement::getItem(handle);

	this->bottom_left = element->position;
	this->z_index = element->z_index;
	this->texture_handle = element->texture;

	this->orig_height = element->size.y;
	this->orig_width = element->size.x;
	this->orig_rotation = 0;
	this->height = this->orig_height;
	this->width = this->orig_width;
	this->rotation = this->orig_rotation;
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
