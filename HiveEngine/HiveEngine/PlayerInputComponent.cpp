#include "PlayerInputComponent.h"

using namespace Hive;

PlayerInputComponent::PlayerInputComponent()
{
	player_unit_handle = -1;
}

void PlayerInputComponent::setPlayerHandle(UnitHandle handle)
{
	using std::placeholders::_1;

	player_unit_handle = handle;
	Unit* unit = Unit::get_component(player_unit_handle);
	DUnit* data = DUnit::getItem(unit->get_type());
	if (data->abilityHandles.size() >= 1)
	{
		left_click = data->abilityHandles[0];
		ServiceLocator::get_input_manager()->registerMouseCallback(GLFW_MOUSE_BUTTON_1, std::bind(&PlayerInputComponent::onleft, this));
	}
	if (data->abilityHandles.size() >= 2)
	{
		right_click = data->abilityHandles[1];
		ServiceLocator::get_input_manager()->registerMouseCallback(GLFW_MOUSE_BUTTON_2, std::bind(&PlayerInputComponent::onright, this));
	}
}

void PlayerInputComponent::onleft()
{
	Unit* unit = Unit::get_component(player_unit_handle);
	Order order;
	order.ability_handle = left_click;
	order.targetPoint = ServiceLocator::get_input_manager()->getMousePositionWorld();
	order.type = AbilityType::POINT_TARGET;
	try
	{
		unit->issue_order(order);
	}
	catch (const OrderException& e)
	{
		printf("Unable to cast: %s\n", e.what());
	}
}

void PlayerInputComponent::onright()
{
	Unit* unit = Unit::get_component(player_unit_handle);
	Order order;
	order.ability_handle = right_click;
	order.targetPoint = ServiceLocator::get_input_manager()->getMousePositionWorld();
	order.type = AbilityType::POINT_TARGET;
	unit->issue_order(order);
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