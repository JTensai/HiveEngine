#pragma once
#include <glm/glm.hpp>

#include "Data.h"
#include "Texture.h"

namespace Hive
{
	class UIElement
	{
	public:
		UIElement();
		UIElement(glm::vec2 bottom_left, float width, float height, DTextureHandle texture_handle);
		~UIElement();
		void update(float delta);
		void draw();

		//private:
		glm::vec2 bottom_left = glm::vec2();
		float width;
		float height;
		float rotation;
		int z_index;
		DTextureHandle texture_handle;
		// type of element
		// each sub element will define its own extra methods that interact with the mouse
	};
}
