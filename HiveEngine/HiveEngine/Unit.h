#pragma once

#include <vector>

#include <glm\glm.hpp>

#include "Actor.h"
#include "Component.h"
#include "Data.h"
#include "ObjectPool.h"
#include "Order.h"
#include "EffectTree.h"
#include "Effects.h"
#include "Exceptions.h"

namespace Hive
{
	class Unit : public Component<Unit>
	{
	private:
		UnitHandle self;
		ActorHandle actor_handle;
		DUnitHandle data_handle;
		AIHandle ai_handle;

		float height;

		Vitals regen; //Provided to avoid dereferencing data pointer in most update loops.
		Vitals max_vitals;

		glm::vec2 target;

		float speed;

		glm::vec2 cached_position;

		Vitals cached_vitals;

		float cached_rotation;

		PlayerHandle player_owner;

		std::vector<AbilityInstance> abilities;

	public:
		Unit();
		void init_unit(UnitHandle self, ActorHandle actor, DUnitHandle data, PlayerHandle player, glm::vec2 position);
		static void preupdate();
		void update_component(float delta);
		void update_abilities(float delta);

		OrderResponse issue_order(Order& order);

		UnitHandle get_handle() const { return self; }
		ActorHandle get_actor() const { return actor_handle; }
		DUnitHandle get_type() const { return data_handle; }
		AIHandle get_AI() const { return ai_handle; }

		void set_AI(AIHandle handle) { ai_handle = handle; }

		void set_target(glm::vec2 target) { Unit::target = target; }

		glm::vec2 get_position() const { return cached_position; }
		void set_position(glm::vec2 pos) { cached_position = pos; }

		Vitals get_vitals() const { return cached_vitals; }
		Vitals get_max_vitals() const { return max_vitals; }
		void set_vitals(Vitals vitals);
		void change_vitals(Vitals delta);

		PlayerHandle get_player() const { return player_owner; }
		void set_player(PlayerHandle player) { player_owner = player; }

		void set_speed(float speed) { this->speed = speed; }

		~Unit();
	};

}
