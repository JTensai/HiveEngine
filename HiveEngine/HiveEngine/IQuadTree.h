#pragma once
#include <glm/glm.hpp>
#include "Unit.h"
#include "Data.h"

namespace Hive {
	class Unit;

	class IQuadTree {
	public:
		virtual void set_dimensions(glm::vec2 map_min, glm::vec2 map_max) = 0;
		virtual void populate_tree(std::vector<Unit*> units_array) = 0;
		virtual void collide() = 0;
		virtual std::vector<UnitHandle> get_units_in_area(glm::vec2 center, float radius) = 0;

		virtual ~IQuadTree() {};
	};
}