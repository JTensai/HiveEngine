#include "ComponentManager.h"
#define C_SIZE 100

namespace Hive
{

	void ComponentManager::initialize()
	{
		AbilityComponent::initialize();
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
		AbilityComponent::update_all(delta);
		AIComponent::update_all(delta);
		BehaviorComponent::update_all(delta);
		Unit::update_all(delta);
	}

	int ComponentManager::spawn_unit(glm::vec2 position, int dunit_handle, int player)
	{
		DUnit* dunit = DUnit::getItem(dunit_handle);

		int actor_handle = Actor::create_component();
		Actor* actor = Actor::get_component(actor_handle);
		actor->loadFromData(dunit->actorDataHandle);

		int unit_handle = Unit::create_component();
		Unit* unit = Unit::get_component(unit_handle);
		unit->init_unit(actor_handle, dunit_handle, player, position);

		return unit_handle;
	}

	void ComponentManager::attach_player_input(int unit_handle)
	{
		player_input_component = PlayerInputComponent();
		player_input_component.setPlayerHandle(unit_handle);
	}

	void ComponentManager::draw(const glm::mat4& VP)
	{
		Actor::draw_all(VP);
		ParticleSystemComponent::draw_all(VP);
	}

	ComponentManager::~ComponentManager()
	{
	}

}