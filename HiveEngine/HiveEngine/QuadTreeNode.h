#pragma once
#include <glm/glm.hpp>

class QuadTreeNode
{
public:
	QuadTreeNode();
	QuadTreeNode(float min_x, float max_x, float min_y, float max_y, int parent_depth, bool is_leaf);
	QuadTreeNode* get_NENode();
	QuadTreeNode* get_SENode();
	QuadTreeNode* get_SWNode();
	QuadTreeNode* get_NWNode();
	float get_x_min();
	float get_x_max();
	float get_y_min();
	float get_y_max();
	int get_number_contained_points();
	void insert(glm::vec2 point);
	void cleanup_tree();

	int get_depth();

	bool get_is_leaf_node();
	glm::vec2 get_contained_point();
	bool is_empty();
	
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
	int number_contained_points;

	bool is_leaf_node;
	glm::vec2 contained_point;

};

