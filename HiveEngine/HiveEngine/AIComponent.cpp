#include "AIComponent.h"

using namespace Hive;

AIComponent::AIComponent()
{
}

void AIComponent::update_component(float delta)
{
	//TODO: update component
	Unit* player_unit = Unit::get_component(player_handle);
	glm::vec2 player_position = player_unit->get_position();
}

AIComponent::~AIComponent()
{
}

void AIComponent::pathfind_a_star(Graph& graph, Node* start, Node* end, BaseHeuristic* heuristic)
{
	PriorityQueue<NodeRecord> open(graph.get_map_width() * graph.get_map_depth());
	vector<NodeRecord> closed;//list of visited nodes

	NodeRecord start_record;
	start_record.node = start;
	start_record.node->set_parent(nullptr);
	start_record.cost_so_far = 0;
	start_record.estimated_total_cost = heuristic->estimate(start);

	open.insert(start_record);

	while (open.size() > 0)
	{
		NodeRecord curr = open.deleteMin();
		closed.push_back(curr);

		if (*curr.node == *end)
		{
			generate_path(curr.node, start);
			return;
		}

		vector<Node*> connecting_nodes = *graph.get_connections(curr.node);

		for (int i = 0; i < connecting_nodes.size(); ++i)
		{
			if (contains(open, connecting_nodes[i]))
			{
				NodeRecord temp = find(open, connecting_nodes[i]);
				float temp_cost = curr.cost_so_far + curr.node->distance_to(connecting_nodes[i]);
				if (temp.cost_so_far > temp_cost)
				{
					open.delete_object(temp);

					//temp.fromNode = &curr;
					temp.node->set_parent(curr.node);
					temp.cost_so_far = temp_cost;
					temp.estimated_total_cost = temp.cost_so_far + heuristic->estimate(curr.node);

					open.insert(temp);
				}
			}
			else if (contains(closed, connecting_nodes[i]))
			{
				NodeRecord temp = find(closed, connecting_nodes[i]);
				float temp_cost = curr.cost_so_far + curr.node->distance_to(connecting_nodes[i]);
				if (temp.cost_so_far > temp_cost)
				{
					remove(closed, temp);

					//temp.fromNode = &curr;
					temp.node->set_parent(curr.node);
					temp.cost_so_far = temp_cost;
					temp.estimated_total_cost = temp.cost_so_far + heuristic->estimate(curr.node);

					closed.push_back(temp);
				}
			}
			else
			{
				NodeRecord to_add;
				to_add.node = connecting_nodes[i];
				//toAdd.fromNode = &curr;
				to_add.node->set_parent(curr.node);
				to_add.cost_so_far = curr.cost_so_far + curr.node->distance_to(to_add.node);
				to_add.estimated_total_cost = to_add.cost_so_far + heuristic->estimate(to_add.node);

				open.insert(to_add);
			}
		}
	}
	//return &vector<Node*>();
}

void AIComponent::generate_path(Node* curr, Node* start)
{
	nav_path.clear();
	nav_path.insert(nav_path.begin(), curr);

	while (curr->get_parent() != nullptr)
	{
		Node* temp = curr;
		curr = curr->get_parent();
		temp->set_parent(nullptr);
		nav_path.insert(nav_path.begin(), curr);
	}
}

bool AIComponent::contains(PriorityQueue<NodeRecord>& pq, Node* node)
{
	int size = pq.size();
	for (int i = 0; i < size; ++i)
	{
		if (*node == *pq.get_index(i).node)
		{
			return true;
		}
	}
	return false;
}

bool AIComponent::contains(vector<NodeRecord>& closed, Node* node)
{
	int size = (int)closed.size();
	for (int i = 0; i < size; ++i)
	{
		if (*node == *closed[i].node)
		{
			return true;
		}
	}
	return false;
}

AIComponent::NodeRecord AIComponent::find(PriorityQueue<NodeRecord>& pq, Node* toFind)
{
	NodeRecord toReturn;
	int size = pq.size();
	for (int i = 0; i < size; ++i)
	{
		NodeRecord temp = pq.get_index(i);
		if (*toFind == *temp.node)
		{
			toReturn = temp;
			break;
		}
	}
	return toReturn;
}

AIComponent::NodeRecord AIComponent::find(vector<NodeRecord>& closed, Node* toFind)
{
	NodeRecord toReturn;
	int size = (int)closed.size();
	for (int i = 0; i < size; ++i)
	{
		NodeRecord temp = closed[i];
		if (*toFind == *temp.node)
		{
			toReturn = temp;
			break;
		}
	}
	return toReturn;
}

void AIComponent::remove(vector<NodeRecord>& closed, NodeRecord toRemove)
{
	for (int i = 0; i < closed.size(); ++i)
	{
		if (toRemove == closed[i])
		{
			closed.erase(closed.begin() + i);
			break;
		}
	}
}

void AIComponent::set_unit_handle(int unit_handle)
{
	this->unit_handle = unit_handle;
}

void AIComponent::set_player_handle(int player_handle)
{
	this->player_handle = player_handle;
}