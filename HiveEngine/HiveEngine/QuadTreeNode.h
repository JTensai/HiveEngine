/*#pragma once
#include "QuadTreeLeafNode.h"
#include <glm/glm.hpp>

class QuadTreeNode
{
public:
	QuadTreeNode();
	QuadTreeNode(float min_x, float max_x, float min_y, float max_y);
	QuadTreeNode* get_NENode();
	QuadTreeNode* get_SENode();
	QuadTreeNode* get_SWNode();
	QuadTreeNode* get_NWNode();
	float get_x_min();
	float get_x_max();
	float get_y_min();
	float get_y_max();
	int get_contained_points();
	virtual void insert(glm::vec2 point);
	void cleanup_tree();
	~QuadTreeNode();

private:
	QuadTreeNode* NENode;
	QuadTreeNode* SENode;
	QuadTreeNode* SWNode;
	QuadTreeNode* NWNode;
	int depth;
	float x_min;
	float x_max;
	float y_min;
	float y_max;
	int contained_points;


};

*/