#pragma once
#include "Actor.h"

namespace Hive
{
	class QuadTreeNode
	{
	public:
		QuadTreeNode();
		QuadTreeNode(float min_x, float max_x, float min_y, float max_y, float coll_threshold, int parent_depth, bool is_leaf);
		//Disclaimer: I named these nodes as if we were using a typical cartesian plane with x increasing as it goes right or east, and
		// y increasing as it goes up or north. This won't line up with the "east" and "north" according to the screen, but the tree 
		// will function all the same.
		QuadTreeNode* get_NENode();
		QuadTreeNode* get_SENode();
		QuadTreeNode* get_SWNode();
		QuadTreeNode* get_NWNode();
		float get_x_min();
		float get_x_max();
		float get_y_min();
		float get_y_max();
		int get_number_contained_points();
		void insert(Unit* unit);
		//void cleanup_tree();

		std::vector<Unit*> get_units_in_area(float area_left, float area_right, float area_bottom, float area_top);

		void collide();

		int get_depth();
		//bool get_is_leaf_node();
		Unit* get_contained_point();
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
		int number_contained_units;
		float collision_threshold;

		bool is_leaf_node;
		Unit* contained_unit;

		std::vector<Unit*> get_contained_units();
		void aggregate_vectors(std::vector<Unit*>& existing_vector, std::vector<Unit*> new_vector);
	};
}