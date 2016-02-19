#pragma once
/*
 ***************************
 * Ability Component
 * The ability component is responsible for maintaining what abilities an entity has access to and the current state of those abilities.
 * This includes information about cooldowns, charges, etc.
 * The ability component is recieves orders from a player input component or an AI component and uses the abilities if possible, or passes them on to the responsible component (e.g. Movement Component).
 * The ability component also notifies the entity's actor at each stage of the ability's use.
 ***************************
 */

#include "Data.h"
#include "Component.h"
#include "ObjectPool.h"

namespace Hive
{
	struct Ability
	{
		DAbility* data;
		float cooldown;
		int charges;
		int charge_max; //Provided to avoid dereferencing data pointer in most update loops.
		int charge_regen; //^
		float charge_cooldown;
		float max_charge_cooldown; //^^^
	};

	class AbilityComponent : public Component<AbilityComponent>
	{
	private:
		ObjectPool<Ability> abilities;
	public:
		AbilityComponent();
		void update_component(float delta, bool is_a);
		~AbilityComponent();
	};

}