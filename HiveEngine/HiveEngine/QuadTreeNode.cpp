#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode() {

}

QuadTreeNode::QuadTreeNode(float min_x, float max_x, float min_y, float max_y, bool is_leaf)
{
	x_min = min_x;
	x_max = max_x;
	y_min = min_y;
	y_max = max_y;

	number_contained_points = 0;
	is_leaf_node = is_leaf;

	if (!is_leaf) {
		SWNode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2, true);
		NWNode = new QuadTreeNode(x_min, x_max / 2, y_max / 2, y_max, true);
		SENode = new QuadTreeNode(x_max / 2, x_max, y_min, y_max / 2, true);
		NENode = new QuadTreeNode(x_max / 2, x_max, y_max / 2, y_max, true);
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
		}
		else {
			glm::vec2 temp_point = contained_point;
			is_leaf_node = false;
			SWNode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2, true);
			NWNode = new QuadTreeNode(x_min, x_max / 2, y_max / 2, y_max, true);
			SENode = new QuadTreeNode(x_max / 2, x_max, y_min, y_max / 2, true);
			NENode = new QuadTreeNode(x_max / 2, x_max, y_max / 2, y_max, true);
			this->insert(temp_point);
			this->insert(point);
		}
	} 
	else {
		if (point.x < x_max / 2) {
			if (point.y < y_max / 2) {
				SWNode->insert(point);
			}
			else {
				NWNode->insert(point);
			}
		}
		else {
			if (point.y < y_max / 2) {
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
	if (SWNode->number_contained_points == 0 && !SWNode->is_leaf_node) {
		SWNode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2, true);
	} else {
		SWNode->cleanup_tree();
	}

	if (NWNode->number_contained_points == 0 && !NWNode->is_leaf_node) {
		NWNode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2, true);
	}
	else {
		NWNode->cleanup_tree();
	}

	if (SENode->number_contained_points == 0 && !SENode->is_leaf_node) {
		SENode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2, true);
	}
	else {
		SENode->cleanup_tree();
	}

	if (NENode->number_contained_points == 0 && !NENode->is_leaf_node) {
		NENode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2, true);
	}
	else {
		NENode->cleanup_tree();
	}

}
