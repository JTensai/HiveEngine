#pragma once
/*
 ***************************
 * AI Component
 * The AI Component is responsible for generating all movement and ability use of non-player controlled entities.
 * Ideally AI behavior will be specified through data, but for the immediate future perhaps one or two hardcoded programs can be selected from in the data.
 * The AI Component sends all of its orders to the entity's ability component, which will forward movement commands to the movement component.
 ***************************
 */


#include "BaseHeuristic.h"
#include "Component.h"
#include "EuclideanHeuristic.h"
#include "Graph.h"
#include "IGameWorld.h"
#include "Node.h"
#include "PriorityQueue.h"
#include "Unit.h"

#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

using namespace std;

namespace Hive
{
	class AIComponent : public Component<AIComponent>
	{
	public:
		//This structure is used to keep track of the information we need for each node
		struct NodeRecord
		{
			Node* node;
			//NodeRecord* fromNode;
			float cost_so_far;
			float estimated_total_cost;
			bool operator!=(const NodeRecord &other) const { return *node != *other.node; }
			bool operator==(const NodeRecord &other) const { return *node == *other.node; }
			bool operator<(const NodeRecord &other) const { return estimated_total_cost < other.estimated_total_cost; }
			bool operator>(const NodeRecord &other) const { return estimated_total_cost > other.estimated_total_cost; }
		};

		AIComponent();
		void update_component(float delta);
		~AIComponent();

		void pathfind_a_star(Graph* graph, Node& start, Node& end, BaseHeuristic& heuristic);
		void set_unit_handle(UnitHandle);
		void set_player_handle(UnitHandle);
		void set_perception_enter_radius(float);
		void set_perception_exit_radius(float);

	private:
		UnitHandle unit_handle;//unit that uses this component
		UnitHandle player_unit_handle;//handle for player's unit (currently assuming there is only one player unit in the game)
		glm::vec2 cached_player_position;
		const float PI = 3.1415926535897;
		float perception_enter_radius;
		float perception_exit_radius;
		float ability_cooldown;

		vector<Node*> nav_path;

		void generate_path(Node* curr, Node* start);
		bool contains(PriorityQueue<NodeRecord>& pq, Node* node);
		bool contains(vector<NodeRecord>& closed, Node* node);
		NodeRecord find(PriorityQueue<NodeRecord>& pq, Node* toFind);
		NodeRecord find(vector<NodeRecord>& closed, Node* toFind);
		void remove(vector<NodeRecord>& closed, NodeRecord toRemove);
		float distance(glm::vec2 a, glm::vec2 b);
		void smooth_path();
		bool ray_clear(Node* start, Node* end);
		void update_movement(float delta);
		void update_ability_use(float delta);
	};

}