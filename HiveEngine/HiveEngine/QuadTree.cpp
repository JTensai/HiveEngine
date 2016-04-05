#include "QuadTree.h"

using namespace Hive;

QuadTree::QuadTree() {
	collision_threshold = .3;
}


void QuadTree::set_dimensions(glm::vec2 map_min, glm::vec2 map_max)
{
	map_minimum = map_min;
	map_maximum = map_max;
}

void QuadTree::populate_tree(std::vector<Unit*> units_array)
{
	if (root != nullptr) {
		delete root;
	}
	root = new QuadTreeNode(map_minimum.x, map_maximum.x, map_minimum.y, map_maximum.y, collision_threshold, 0, false);

	for (int i = 0; i < units_array.size(); i++) {
		root->insert(units_array[i]);
	}
	//root->cleanup_tree(); Don't need this right now, if we later decide to build out a dummy tree before populating (instead of expanding
	// as we insert) then this will be useful. Due to that, I am not removing the functions I've built in just yet.
}

void QuadTree::collide() {
	root->collide();
}

std::vector<glm::vec2> QuadTree::get_units_in_area(glm::vec2 center, float radius) {
	//Philosophy: find the bounding box of the circle made by the area, use those corners to isolate the quads we want, 
		//then grab everything from those and return them.
	return std::vector<glm::vec2>();
}

QuadTree::~QuadTree()
{
	if (root != nullptr) {
		delete root;
	}
}
