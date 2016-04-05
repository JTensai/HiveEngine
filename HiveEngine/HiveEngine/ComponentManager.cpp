#include "ComponentManager.h"
#define C_SIZE 100

namespace Hive
{

	void ComponentManager::initialize()
	{
		Actor::initialize();
		AIComponent::initialize();
		BehaviorComponent::initialize();
		ParticleSystemComponent::initialize();
		Unit::initialize();
	}

	void ComponentManager::load()
	{
	}

	void ComponentManager::update_free(float delta)
	{
		Actor::update_all(delta);
		ParticleSystemComponent::update_all(delta);
	}

	void ComponentManager::update_fixed(float delta)
	{
		//player input component does not derive from component, its in a bit of a hacked together state right now.
		player_input_component.update(delta);
		AIComponent::update_all(delta);
		BehaviorComponent::update_all(delta);
		Unit::update_all(delta);
	}

	UnitHandle ComponentManager::spawn_unit(glm::vec2 position, DUnitHandle dunit_handle, PlayerHandle player)
	{
		DUnit* dunit = DUnit::getItem(dunit_handle);

		ActorHandle actor_handle = Actor::create_component();
		Actor* actor = Actor::get_component(actor_handle);
		actor->loadFromData(dunit->actorDataHandle);

		UnitHandle unit_handle = Unit::create_component();
		Unit* unit = Unit::get_component(unit_handle);
		unit->init_unit(unit_handle, actor_handle, dunit_handle, player, position);

		return unit_handle;
	}

	UnitHandle ComponentManager::spawn_ai_unit(glm::vec2 position, DUnitHandle dunit_handle, PlayerHandle player, UnitHandle player_unit_handle)
	{
		UnitHandle unit_handle = spawn_unit(position, dunit_handle, player);

		AIHandle ai_component_handle = AIComponent::create_component();
		AIComponent* ai_component = AIComponent::get_component(ai_component_handle);
		ai_component->set_unit_handle(unit_handle);
		ai_component->set_player_handle(player_unit_handle);
		ai_component->set_perception_enter_radius(4.5f);
		ai_component->set_perception_exit_radius(8.0f);

		Unit::get_component(unit_handle)->set_AI(ai_component_handle);

		return unit_handle;
	}

	void ComponentManager::attach_player_input(UnitHandle unit_handle)
	{
		player_input_component = PlayerInputComponent();
		player_input_component.setPlayerHandle(unit_handle);
	}

	void ComponentManager::draw(const glm::mat4& VP)
	{
		ServiceLocator::get_graphics()->update_view_projection_matrix(VP);

		Actor::draw_all(VP);
		ParticleSystemComponent::draw_all(VP);

		ServiceLocator::get_graphics()->draw_all();
	}

	ComponentManager::~ComponentManager()
	{
	}
}