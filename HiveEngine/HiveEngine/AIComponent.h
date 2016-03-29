#pragma once
/*
 ***************************
 * AI Component
 * The AI Component is responsible for generating all movement and ability use of non-player controlled entities.
 * Ideally AI behavior will be specified through data, but for the immediate future perhaps one or two hardcoded programs can be selected from in the data.
 * The AI Component sends all of its orders to the entity's ability component, which will forward movement commands to the movement component.
 ***************************
 */

#include "Component.h"

#include <vector>

#include "BaseHeuristic.h"
#include "Graph.h"
#include "Node.h"
#include "PriorityQueue.h"

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

		std::vector<Node*>* pathfind_a_star(Graph& graph, Node* start, Node* end, BaseHeuristic* heuristic);
		void set_unit_handle(int);
		void set_player_handle(int);

	private:
		int unit_handle;
		int player_handle;

		vector<Node*>* generate_path(Node* curr, Node* start);
		bool contains(PriorityQueue<NodeRecord>& pq, Node* node);
		bool contains(vector<NodeRecord>& closed, Node* node);
		NodeRecord find(PriorityQueue<NodeRecord>& pq, Node* toFind);
		NodeRecord find(vector<NodeRecord>& closed, Node* toFind);
		void remove(vector<NodeRecord>& closed, NodeRecord toRemove);
	};

}