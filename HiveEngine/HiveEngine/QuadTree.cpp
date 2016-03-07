/*#include "QuadTree.h"


QuadTree::QuadTree(float map_width, float map_height) {
	width = map_width;
	height = map_height;
}

void QuadTree::populate_tree(std::vector<glm::vec2> points_array)
{
	root = new QuadTreeNode(0, width, 0, height);

	for (int i = 0; i < points_array.size; i++) {
		root->insert(points_array[i]);
	}

	//root->cleanup_tree(); Don't need this right now, if we later decide to build out a dummy tree before populating (instead of expanding
	// as we insert) then this will be useful. Due to that, I am not removing the functions I've built in just yet.
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
*/