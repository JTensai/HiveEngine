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

		glm::vec2 position_a;
		glm::vec2 position_b;

		float rotation_a;
		float rotation_b;

		float height;

		Vitals vitals_a;
		Vitals vitals_b;
		Vitals regen; //Provided to avoid dereferencing data pointer in most update loops.
		Vitals max_vitals;

		glm::vec2 target;

		float speed;

		inline glm::vec2& cached_position(bool is_a) { return (is_a) ? position_b : position_a; }
		inline glm::vec2& new_position(bool is_a) { return (is_a) ? position_a : position_b; }

		inline Vitals& cached_vitals(bool is_a) { return (is_a) ? vitals_b : vitals_a; }
		inline Vitals& new_vitals(bool is_a) { return (is_a) ? vitals_a : vitals_b; }

		inline float& cached_rotation(bool is_a) { return (is_a) ? rotation_b : rotation_a; }
		inline float& new_rotation(bool is_a) { return (is_a) ? rotation_a : rotation_b; }

	public:
		Unit();
		void init_unit(int actor, int data, glm::vec2 position);
		void update_component(float delta, bool is_a);

		int get_actor() { return actorHandle; }

		void set_target(glm::vec2 target) { Unit::target = target; }

		glm::vec2 get_position(bool is_a) { return cached_position(is_a); }
		void set_position(bool is_a, glm::vec2 pos) { new_position(is_a) = pos; }

		Vitals get_vitals(bool is_a) { return cached_vitals(is_a); }
		void set_vitals(bool is_a, Vitals vitals) { new_vitals(is_a) = vitals; }

		~Unit();
	};

}
