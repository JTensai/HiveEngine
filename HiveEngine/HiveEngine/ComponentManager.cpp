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

	void ComponentManager::update_free(float delta, bool is_a)
	{
		Actor::update(delta, is_a);
		ParticleSystemComponent::update(delta, is_a);
	}

	void ComponentManager::update_fixed(float delta, bool is_a)
	{
		AbilityComponent::update(delta, is_a);
		AIComponent::update(delta, is_a);
		BehaviorComponent::update(delta, is_a);
		Unit::update(delta, is_a);
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