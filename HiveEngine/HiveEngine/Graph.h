#pragma once

#include <math.h>
#include "Node.h"
#include "Connection.h"
#include <map>
#include <vector>
#include "BaseHeuristic.h"
#include "PriorityQueue.h"

using namespace std;

class Graph
{
private:
	// 1 is walkable
	char temp_map[8][8] =
	{
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','0','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' }
	};
	int num_rows;
	int num_cols;

	map<int, vector<Node*> > connections;
	
public:
	Graph();
	template <size_t size_x, size_t size_y>
	Graph(char(&char_map)[size_x][size_y]):numRows(size_x), numCols(size_y)
	{
		//connections = new Connections[size_x * size_ y][9];
		Node* node_map[size_x][size_y];

		//create map of Nodes
		for (int i = 0; i < num_rows; ++i)
		{
			for (int j = 0; j < num_cols; ++j)
			{
				node_map[i][j] = new Node(i, j);
			}
		}

		//For each node create a list of Connections
		for (int i = 0; i < num_rows; ++i)
		{
			for (int j = 0; j < num_cols; ++j)
			{
				Node* curr_node = node_map[i][j];
				int key = (i * num_cols) + j;
				connections[key] = vector<Node*>();
				if (i - 1 >= 0 && char_map[i - 1][j] == '1')
				{
					connections[key].push_back(node_map[i - 1][j]);
				}
				if (i + 1 < numRows && char_map[i + 1][j] == '1')
				{
					connections[key].push_back(node_map[i + 1][j]);
				}
				if (j - 1 >= 0 && char_map[i][j - 1] == '1')
				{
					connections[key].push_back(node_map[i][j - 1]);
				}
				if (j + 1 < numCols && char_map[i][j + 1] == '1')
				{
					connections[key].push_back(node_map[i][j + 1]);
				}
			}
		}
	}
	~Graph();
	// Returns an array of connections(of class
	// Connection) outgoing from the given node
	vector<Node*>* get_connections(Node* fromNode);

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

	vector<Node*>* pathfind_a_star(Graph graph, Node* start, Node* end, BaseHeuristic* heuristic)
	{
		PriorityQueue<NodeRecord> open(graph.num_rows * graph.num_cols);
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
				return generate_path(curr.node,start);
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
						remove(closed,temp);

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
		return &vector<Node*>();
	}

	vector<Node*>* generate_path(Node* curr, Node* start)
	{
		vector<Node*> path;
		path.insert(path.begin(), curr);

		while (curr->get_parent() != nullptr)
		{
			Node* temp = curr;
			curr = curr->get_parent();
			temp->set_parent(nullptr);
			path.insert(path.begin(),curr);
		}

		return &path;
	}

	bool contains(PriorityQueue<NodeRecord>& pq, Node* node)
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

	bool contains(vector<NodeRecord>& closed, Node* node)
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

	NodeRecord find(PriorityQueue<NodeRecord>& pq, Node* toFind)
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

	NodeRecord find(vector<NodeRecord>& closed, Node* toFind)
	{
		NodeRecord toReturn;
		int size = (int) closed.size();
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

	void remove(vector<NodeRecord>& closed, NodeRecord toRemove)
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
};

