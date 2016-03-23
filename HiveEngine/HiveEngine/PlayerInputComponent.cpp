#include "PlayerInputComponent.h"

using namespace Hive;

PlayerInputComponent::PlayerInputComponent()
{
	player_unit_handle = -1;
}

void PlayerInputComponent::update(float delta)
{
	if (player_unit_handle >= 0)
	{
		glm::vec2 mov_dir = glm::vec2(0);
		if (ServiceLocator::get_input_manager()->isKeyDown(GLFW_KEY_W))
		{
			mov_dir.y -= 1.0;
		}
		if (ServiceLocator::get_input_manager()->isKeyDown(GLFW_KEY_A))
		{
			mov_dir.x -= 1.0;
		}
		if (ServiceLocator::get_input_manager()->isKeyDown(GLFW_KEY_S))
		{
			mov_dir.y += 1.0;
		}
		if (ServiceLocator::get_input_manager()->isKeyDown(GLFW_KEY_D))
		{
			mov_dir.x += 1.0;
		}

		if (mov_dir.x || mov_dir.y)
		{
			mov_dir = glm::normalize(mov_dir) * 0.05f;

			Unit* unit = Unit::get_component(player_unit_handle);
			unit->set_target(unit->get_position() + mov_dir);
		}
	}
}

PlayerInputComponent::~PlayerInputComponent()
{
}