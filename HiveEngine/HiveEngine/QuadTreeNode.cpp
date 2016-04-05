#include "QuadTreeNode.h"

using namespace Hive;

QuadTreeNode::QuadTreeNode() {

}

QuadTreeNode::QuadTreeNode(float min_x, float max_x, float min_y, float max_y, float coll_threshold, int parent_depth, bool is_leaf)
{
	x_min = min_x;
	x_max = max_x;
	y_min = min_y;
	y_max = max_y;

	collision_threshold = coll_threshold;

	depth = parent_depth + 1;
	contained_unit = nullptr;

	number_contained_units = 0;
	is_leaf_node = is_leaf;

	if (!is_leaf) {
		float x_mid = x_min + (x_max - x_min) / 2;
		float y_mid = y_min + (y_max - y_min) / 2;
		SWNode = new QuadTreeNode(x_min, x_mid, y_min, y_mid, collision_threshold, depth, true);
		NWNode = new QuadTreeNode(x_min, x_mid, y_mid, y_max, collision_threshold, depth, true);
		SENode = new QuadTreeNode(x_mid, x_max, y_min, y_mid, collision_threshold, depth, true);
		NENode = new QuadTreeNode(x_mid, x_max, y_mid, y_max, collision_threshold, depth, true);
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
	return number_contained_units;
}

Unit* QuadTreeNode::get_contained_point() {
	return contained_unit;
}

bool QuadTreeNode::is_empty() {
	return number_contained_units == 0;
}

void QuadTreeNode::insert(Unit* unit) {
	if (unit->get_position().x < x_min || unit->get_position().x > x_max
		|| unit->get_position().y < y_min || unit->get_position().y > y_max)
	{//ignore anything that falls outside of the dimensions of the node. 
	//Ideally, this would be used to trigger 'collision' with the edges of the world
		return;
	}

	if (is_leaf_node) {
		if (this->is_empty()) {
			contained_unit = unit;
			number_contained_units++;
		}
		else {//There's already a point in this leaf node, so we expand the node and recursively insert both the current point and the new point into the pile
			is_leaf_node = false;
			Unit* temp_unit = contained_unit;
			contained_unit = nullptr;
			number_contained_units--;

			float x_mid = x_min + (x_max - x_min) / 2;
			float y_mid = y_min + (y_max - y_min) / 2;
			SWNode = new QuadTreeNode(x_min, x_mid, y_min, y_mid, collision_threshold, depth, true);
			NWNode = new QuadTreeNode(x_min, x_mid, y_mid, y_max, collision_threshold, depth, true);
			SENode = new QuadTreeNode(x_mid, x_max, y_min, y_mid, collision_threshold, depth, true);
			NENode = new QuadTreeNode(x_mid, x_max, y_mid, y_max, collision_threshold, depth, true);
			this->insert(temp_unit);
			this->insert(unit);
		}
	} 
	else {
		float x_mid = x_min + (x_max - x_min) / 2;
		float y_mid = y_min + (y_max - y_min) / 2;

		if (unit->get_position().x < x_mid) {
			if (unit->get_position().y < y_mid) {
				SWNode->insert(unit);
			}
			else {
				NWNode->insert(unit);
			}
		}
		else {
			if (unit->get_position().y < y_mid) {
				SENode->insert(unit);
			}
			else {
				NENode->insert(unit);
			}
		}
		number_contained_units++;
	}
}

/*void QuadTreeNode::cleanup_tree() {

	float x_mid = x_min + (x_max - x_min) / 2;
	float y_mid = y_min + (y_max - y_min) / 2;

	if (SWNode->number_contained_units == 0 && !SWNode->is_leaf_node) {
		SWNode = new QuadTreeNode(x_min, x_mid, y_min, y_mid, depth, true);
	} else {
		SWNode->cleanup_tree();
	}

	if (NWNode->number_contained_units == 0 && !NWNode->is_leaf_node) {
		NWNode = new QuadTreeNode(x_min, x_mid, y_mid, y_max, depth, true);
	}
	else {
		NWNode->cleanup_tree();
	}

	if (SENode->number_contained_units == 0 && !SENode->is_leaf_node) {
		SENode = new QuadTreeNode(x_mid, x_max, y_min, y_mid, depth, true);
	}
	else {
		SENode->cleanup_tree();
	}

	if (NENode->number_contained_units == 0 && !NENode->is_leaf_node) {
		NENode = new QuadTreeNode(x_mid, x_max, y_mid, y_max, depth, true);
	}
	else {
		NENode->cleanup_tree();
	}

}*/

void QuadTreeNode::collide() {
	if (number_contained_units <= 1) {
		return;
	}
	float quad_size = x_max - x_min;//or y_max - y_min
	if (quad_size / (float)number_contained_units < collision_threshold) {//not enough points to warrant searching, keep recursing
		SWNode->collide();
		NWNode->collide();
		SENode->collide();
		NENode->collide();
	}
	else {//iterate over all units and find collision potential
		std::vector<Unit*> contained_units = get_contained_units();
		for (int i = 0; i < contained_units.size() - 1; i++) {
			for (int j = i + 1; j < contained_units.size(); j++) {
				float distance = glm::distance(contained_units[i]->get_position(), contained_units[j]->get_position());
				//Actor* actor_0 = Actor::get_component(contained_units[i]->get_actor());
				//Actor* actor_1 = Actor::get_component(contained_units[j]->get_actor());
				//if (actor_0->somehow_get_size_of_actor < distance) then do a colliding thing
				if (distance < 0.5) {
					std::cout << "Some things are very close!!!!";
				}
			}
		}
	}
}

std::vector<Unit*> QuadTreeNode::get_contained_units() {
	std::vector<Unit*> contained_units = std::vector<Unit*>();
	if (number_contained_units == 1) {
		contained_units.push_back(contained_unit);
	} else if (number_contained_units > 1) {
		aggregate_vectors(contained_units, SWNode->get_contained_units());
		aggregate_vectors(contained_units, NWNode->get_contained_units());
		aggregate_vectors(contained_units, SENode->get_contained_units());
		aggregate_vectors(contained_units, NENode->get_contained_units());
	}
	return contained_units;
}

void QuadTreeNode::aggregate_vectors(std::vector<Unit*>& existing_vector, std::vector<Unit*> new_vector) {
	for (int i = 0; i < new_vector.size(); i++) {
		existing_vector.push_back(new_vector[i]);
	}
}
