#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode() {

}

QuadTreeNode::QuadTreeNode(float min_x, float max_x, float min_y, float max_y, int parent_depth, bool is_leaf)
{
	x_min = min_x;
	x_max = max_x;
	y_min = min_y;
	y_max = max_y;

	depth = parent_depth + 1;
	contained_point = glm::vec2();

	number_contained_points = 0;
	is_leaf_node = is_leaf;

	if (!is_leaf) {
		SWNode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2, depth, true);
		NWNode = new QuadTreeNode(x_min, x_max / 2, y_max / 2, y_max, depth, true);
		SENode = new QuadTreeNode(x_max / 2, x_max, y_min, y_max / 2, depth, true);
		NENode = new QuadTreeNode(x_max / 2, x_max, y_max / 2, y_max, depth, true);
	}
}

QuadTreeNode::~QuadTreeNode()
{
	if (NENode != nullptr) {
		delete NENode;
	}
	if (SENode != nullptr) {
		delete SENode;
	}
	if (SWNode != nullptr) {
		delete SWNode;
	}
	if (NWNode != nullptr) {
		delete NWNode;
	}
}

int QuadTreeNode::get_depth() {
	return depth;
}

QuadTreeNode* QuadTreeNode::get_NENode() {
	return NENode;
}
QuadTreeNode* QuadTreeNode::get_SENode() {
	return SENode;
}
QuadTreeNode* QuadTreeNode::get_SWNode() {
	return SWNode;
}
QuadTreeNode* QuadTreeNode::get_NWNode() {
	return NWNode;
}

float QuadTreeNode::get_x_min() {
	return x_min;
}
float QuadTreeNode::get_x_max() {
	return x_max;
}
float QuadTreeNode::get_y_min() {
	return y_min;
}
float QuadTreeNode::get_y_max() {
	return y_max;
}

int QuadTreeNode::get_number_contained_points() {
	return number_contained_points;
}

glm::vec2 QuadTreeNode::get_contained_point() {
	return contained_point;
}

bool QuadTreeNode::is_empty() {
	return number_contained_points == 0;
}

void QuadTreeNode::insert(glm::vec2 point) {
	if (is_leaf_node) {
		if (this->is_empty()) {
			contained_point = point;
			number_contained_points++;
		}
		else {//There's already a point in this leaf node, so we expand the node and recursively insert both the current point and the new point into the pile
			is_leaf_node = false;
			glm::vec2 temp_point = contained_point;
			contained_point = glm::vec2();
			if (depth >= 7) {
				char weak = 'a';
			}
			float x_mid = x_min + (x_max - x_min) / 2;
			float y_mid = y_min + (y_max - y_min) / 2;
			SWNode = new QuadTreeNode(x_min, x_mid, y_min, y_mid, depth, true);
			NWNode = new QuadTreeNode(x_min, x_mid, y_mid, y_max, depth, true);
			SENode = new QuadTreeNode(x_mid, x_max, y_min, y_mid, depth, true);
			NENode = new QuadTreeNode(x_mid, x_max, y_mid, y_max, depth, true);
			number_contained_points--;
			this->insert(temp_point);
			this->insert(point);
		}
	} 
	else {
		float x_mid = x_min + (x_max - x_min) / 2;
		float y_mid = y_min + (y_max - y_min) / 2;

		if (point.x < x_mid) {
			if (point.y < y_mid) {
				SWNode->insert(point);
			}
			else {
				NWNode->insert(point);
			}
		}
		else {
			if (point.y < y_mid) {
				SENode->insert(point);
			}
			else {
				NENode->insert(point);
			}
		}
		number_contained_points++;
	}
}

void QuadTreeNode::cleanup_tree() {

	float x_mid = x_min + (x_max - x_min) / 2;
	float y_mid = y_min + (y_max - y_min) / 2;

	if (SWNode->number_contained_points == 0 && !SWNode->is_leaf_node) {
		SWNode = new QuadTreeNode(x_min, x_mid, y_min, y_mid, depth, true);
	} else {
		SWNode->cleanup_tree();
	}

	if (NWNode->number_contained_points == 0 && !NWNode->is_leaf_node) {
		NWNode = new QuadTreeNode(x_min, x_mid, y_mid, y_max, depth, true);
	}
	else {
		NWNode->cleanup_tree();
	}

	if (SENode->number_contained_points == 0 && !SENode->is_leaf_node) {
		SENode = new QuadTreeNode(x_mid, x_max, y_min, y_mid, depth, true);
	}
	else {
		SENode->cleanup_tree();
	}

	if (NENode->number_contained_points == 0 && !NENode->is_leaf_node) {
		NENode = new QuadTreeNode(x_mid, x_max, y_mid, y_max, depth, true);
	}
	else {
		NENode->cleanup_tree();
	}

}
