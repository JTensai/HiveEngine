#pragma once

#include <glm/glm.hpp>

#include "AbilityComponent.h"
#include "Actor.h"
#include "AIComponent.h"
#include "BehaviorComponent.h"
#include "ParticleSystemComponent.h"
#include "PlayerInputComponent.h"
#include "IComponentManager.h"
#include "Unit.h"
#include "ParticleSystemData.h"

namespace Hive
{

	class ComponentManager : public IComponentManager
	{
	private:
		// Exists as a bit of a hack assuming we won't need more than one for quite some time.
		PlayerInputComponent player_input_component;

	public:
		ComponentManager() {};

		void initialize();
		void load();
		void update_free(float delta);
		void update_fixed(float delta);
		UnitHandle spawn_unit(glm::vec2 position, DUnitHandle dunit_handle, PlayerHandle player);
		UnitHandle spawn_ai_unit(glm::vec2 position, DUnitHandle dunit_handle, PlayerHandle player, UnitHandle player_unit_handle);
		void attach_player_input(UnitHandle unit_handle);
		void draw(const glm::mat4& VP);

		~ComponentManager();
	};

}