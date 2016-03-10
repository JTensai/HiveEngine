/*#pragma once
#include "QuadTreeNode.h"
#include <vector>
#include <glm\glm.hpp>

class QuadTree
{
public:
	QuadTree(float map_width, float map_height);
	QuadTreeNode* get_root();

	void populate_tree(std::vector<glm::vec2> points_array);
	~QuadTree();

private:
	QuadTreeNode* root;
	float width;
	float height;
};

*/