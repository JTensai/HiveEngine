#pragma once
/*
 ***************************
 * Behavior Component
 * The behavior component is responsible for maintaining and updating any behaviors on its owning entity.
 * Methods should be exposed to allow other systems to query the entity's behaviors and their states.
 ***************************
 */

#include "Component.h"
#include "Data.h"
#include "ObjectPool.h"

namespace Hive
{
	struct Behavior
	{
		DBehavior* data;
		bool has_duration; //Provided to avoid dereferencing data pointer in most update loops.
		float duration;
		float period; //^^^
		int period_count;
		int max_periods; //^^^^^
		int stack_count;
	};

	class BehaviorComponent : public Component<BehaviorComponent>
	{
	private:
		ObjectPool<Behavior> behaviors;
	public:
		BehaviorComponent();
		void update_component(float delta, bool is_a);
		~BehaviorComponent();
	};

}