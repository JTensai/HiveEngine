#pragma once
#include "QuadTreeNode.h"
#include "Unit.h"
#include <vector>
#include <glm\glm.hpp>

namespace Hive 
{
	class QuadTree
	{
	public:
		QuadTree(float map_width, float map_height);
		QuadTreeNode* get_root();
		void collide();

		void populate_tree(std::vector<Unit*> units_array);
		~QuadTree();

	private:
		QuadTreeNode* root;
		float width;
		float height;
		float collision_threshold;
	};
}
