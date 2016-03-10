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
		PlayerInputComponent pic;
	public:
		ComponentManager() {};

		void initialize();
		void load();
		void update_free(float delta, bool is_a);
		void update_fixed(float delta, bool is_a);
		void draw(const glm::mat4& VP);

		~ComponentManager();
	};

}