#include "QuadTree.h"

using namespace Hive;

QuadTree::QuadTree(float map_width, float map_height) {
	width = map_width;
	height = map_height;
	collision_threshold = 1;
}

void QuadTree::populate_tree(std::vector<Unit*> units_array)
{
	root = new QuadTreeNode(0, width, 0, height, collision_threshold, 0, false);

	for (int i = 0; i < units_array.size(); i++) {
		root->insert(units_array[i]);
	}
	//root->cleanup_tree(); Don't need this right now, if we later decide to build out a dummy tree before populating (instead of expanding
	// as we insert) then this will be useful. Due to that, I am not removing the functions I've built in just yet.
}

void QuadTree::collide() {
	root->collide();
}

QuadTreeNode* QuadTree::get_root() {
	return root;
}


QuadTree::~QuadTree()
{
	if (root != nullptr) {
		delete root;
	}
}
