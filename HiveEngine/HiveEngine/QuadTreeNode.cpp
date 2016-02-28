#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode() {

}

QuadTreeNode::QuadTreeNode(float min_x, float max_x, float min_y, float max_y)
{
	x_min = min_x;
	x_max = max_x;
	y_min = min_y;
	y_max = max_y;
	SWNode = new QuadTreeLeafNode();
	NWNode = new QuadTreeLeafNode();
	SENode = new QuadTreeLeafNode();
	NENode = new QuadTreeLeafNode();
	contained_points = 0;
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

int QuadTreeNode::get_contained_points() {
	return contained_points;
}

void QuadTreeNode::insert(glm::vec2 point) {
	if (point.x < x_max / 2) {
		if (point.y < y_max / 2) {
			QuadTreeLeafNode* SWLeaf = dynamic_cast<QuadTreeLeafNode*>(SWNode);
			if (SWLeaf) {
				if (SWLeaf->get_is_empty()) {
					SWLeaf->insert(point);
				}
				else {
					glm::vec2 previous_point = SWLeaf->get_contained_point();
					SWNode = new QuadTreeNode(x_min, x_max / 2, y_min, y_max / 2);
					SWNode->insert(previous_point);
					SWNode->insert(point);
				}
			}
			else {
				SWNode->insert(point);
			}
		}
		else {
			QuadTreeLeafNode* NWLeaf = dynamic_cast<QuadTreeLeafNode*>(NWNode);
			if (NWLeaf) {
				if (NWLeaf->get_is_empty()) {
					NWLeaf->insert(point);
				}
				else {
					glm::vec2 previous_point = NWLeaf->get_contained_point();
					NWNode = new QuadTreeNode(x_min, x_max / 2, y_max / 2, y_max);
					NWNode->insert(previous_point);
					NWNode->insert(point);
				}
			}
			else {
				NWNode->insert(point);
			}
		}
	}
	else {
		if (point.y < y_max / 2) {
			QuadTreeLeafNode* SELeaf = dynamic_cast<QuadTreeLeafNode*>(SENode);
			if (SELeaf) {
				if (SELeaf->get_is_empty()) {
					SELeaf->insert(point);
				}
				else {
					glm::vec2 previous_point = SELeaf->get_contained_point();
					SENode = new QuadTreeNode(x_max / 2, x_max, y_min, y_max / 2);
					SENode->insert(previous_point);
					SENode->insert(point);
				}
			}
			else {
				SENode->insert(point);
			}
		}
		else {
			QuadTreeLeafNode* NELeaf = dynamic_cast<QuadTreeLeafNode*>(NENode);
			if (NELeaf) {
				if (NELeaf->get_is_empty()) {
					NELeaf->insert(point);
				}
				else {
					glm::vec2 previous_point = NELeaf->get_contained_point();
					NENode = new QuadTreeNode(x_max / 2, x_max, y_max / 2, y_max);
					NENode->insert(previous_point);
					NENode->insert(point);
				}
			}
			else {
				NENode->insert(point);
			}
		}
	}
	contained_points++;
}

void QuadTreeNode::cleanup_tree() {
	if (SWNode->get_contained_points() == 0) {
		SWNode = new QuadTreeLeafNode();
	} else {
		SWNode->cleanup_tree();
	}

	if (NWNode->get_contained_points() == 0) {
		NWNode = new QuadTreeLeafNode();
	} else {
		NWNode->cleanup_tree();
	}

	if (SENode->get_contained_points() == 0) {
		SENode = new QuadTreeLeafNode();
	}
	else {
		SENode->cleanup_tree();
	}

	if (NENode->get_contained_points() == 0) {
		NENode = new QuadTreeLeafNode();
	}
	else {
		NENode->cleanup_tree();
	}

}
