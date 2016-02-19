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
		Vitals vitals_a;
		Vitals vitals_b;
		Vitals regen; //Provided to avoid dereferencing data pointer in most update loops.

		inline glm::vec2 cached_position(bool is_a) { return (is_a) ? position_b : position_a; }
		inline glm::vec2 new_position(bool is_a) { return (is_a) ? position_a : position_b; }

		inline Vitals cached_vitals(bool is_a) { return (is_a) ? vitals_b : vitals_a; }
		inline Vitals new_vitals(bool is_a) { return (is_a) ? vitals_b : vitals_a; }
	public:
		Unit();
		void update_component(float delta, bool is_a);
		~Unit();
	};

}