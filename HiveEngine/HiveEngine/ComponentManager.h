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
		int spawn_unit(glm::vec2 position, int dunit_handle, int player);
		int spawn_ai_unit(glm::vec2 position, int dunit_handle, int player);
		void attach_player_input(int unit_handle);
		void draw(const glm::mat4& VP);

		~ComponentManager();
	};

}