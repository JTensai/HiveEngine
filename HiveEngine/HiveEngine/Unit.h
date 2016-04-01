#pragma once

#include <vector>

#include <glm\glm.hpp>

#include "Actor.h"
#include "Component.h"
#include "Data.h"
#include "ObjectPool.h"

namespace Hive
{
	class Unit : public Component<Unit>
	{
	private:
		int actorHandle; //Actor
		int dataHandle; //DUnit

		float height;

		Vitals regen; //Provided to avoid dereferencing data pointer in most update loops.
		Vitals max_vitals;

		glm::vec2 target;

		float speed;

		glm::vec2 cached_position;
		glm::vec2 new_position;

		Vitals cached_vitals;
		Vitals new_vitals;

		float cached_rotation;
		float new_rotation;

		int player_owner;

	public:
		Unit();
		void init_unit(int actor, int data, int player, glm::vec2 position);
		void update_component(float delta);

		int get_actor() { return actorHandle; }

		void set_target(glm::vec2 target) { Unit::target = target; }

		glm::vec2 get_position() { return cached_position; }
		void set_position(glm::vec2 pos) { new_position = pos; }

		Vitals get_vitals() { return cached_vitals; }
		void set_vitals(Vitals vitals) { new_vitals = vitals; }

		int get_player() { return player_owner; }
		void set_player(int player) { player_owner = player; }

		void set_speed(float speed) { this->speed = speed; }

		~Unit();
	};

}
