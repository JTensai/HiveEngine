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
		Actor::update(delta);
		ParticleSystemComponent::update(delta);
	}

	void ComponentManager::update_fixed(float delta)
	{
		pic.update(delta);
		AbilityComponent::update(delta);
		AIComponent::update(delta);
		BehaviorComponent::update(delta);
		Unit::update(delta);
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
		pic = PlayerInputComponent();
		pic.setPlayerHandle(unit_handle);
	}

	void ComponentManager::draw(const glm::mat4& VP)
	{
		Actor::draw(VP);
		ParticleSystemComponent::draw(VP);
	}

	ComponentManager::~ComponentManager()
	{
	}

}