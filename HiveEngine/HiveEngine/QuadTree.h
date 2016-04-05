#pragma once

#include "IQuadTree.h"
#include "QuadTreeNode.h"

namespace Hive 
{
	class QuadTree : public IQuadTree
	{
	public:
		QuadTree();
		void set_dimensions(glm::vec2 map_min, glm::vec2 map_max);
		void populate_tree(std::vector<Unit*> units_array);
		void collide();

		std::vector<UnitHandle> get_units_in_area(glm::vec2 center, float radius);

		~QuadTree();

	private:
		QuadTreeNode* root;
		glm::vec2 map_minimum;
		glm::vec2 map_maximum;
		float collision_threshold;
	};
}
