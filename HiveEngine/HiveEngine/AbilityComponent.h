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

namespace Hive
{

	class AbilityComponent
	{
	public:
		AbilityComponent();
		void update(float delta);
		~AbilityComponent();
	};

}