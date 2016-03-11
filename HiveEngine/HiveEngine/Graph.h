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
	char tempMap[8][8] =
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
	int numRows;
	int numCols;
	//Connection* connections;// [size_x][size_y][9];
	map<int, vector<Node*> > connections;
	
public:
	Graph();
	template <size_t size_x, size_t size_y>
	Graph(char(&map)[size_x][size_y]);
	~Graph();
	// Returns an array of connections(of class
	// Connection) outgoing from the given node
	vector<Node*>* getConnections(Node* fromNode);

	//This structure is used to keep track of the information we need for each node
	struct NodeRecord
	{
		Node* node;
		Node* fromNode;
		float costSoFar;
		float estimatedTotalCost;
		bool operator!=(const NodeRecord &other) const { node != other.node || fromNode != other.fromNode; }
		bool operator==(const NodeRecord &other) const { node == other.node && fromNode != other.fromNode; }
		bool operator<(const NodeRecord &other) const { estimatedTotalCost < other.estimatedTotalCost; }
		bool operator>(const NodeRecord &other) const { estimatedTotalCost > other.estimatedTotalCost; }
	};

	vector<Node*>* pathfindAStar(Graph graph, Node* start, Node* end, BaseHeuristic heuristic)
	{
		PriorityQueue<NodeRecord> open(graph.numRows * graph.numCols);
		vector<NodeRecord> closed;

		NodeRecord startRecord;
		startRecord.node = start;
		startRecord.fromNode = nullptr;
		startRecord.costSoFar = 0;
		startRecord.estimatedTotalCost = heuristic.estimate(start);

		open.insert(startRecord);

		while (open.size() > 0)
		{
			NodeRecord curr = open.deleteMin();
			closed.push_back(curr);

			if (curr.node == end)
			{
				//more must go here
				vector<Node*> path;
				return &path;
			}

			vector<Node*> connectingNodes = *graph.getConnections(curr.node);

			for (int i = 0; i < connectingNodes.size(); ++i)
			{
				if (contains(open, connectingNodes[i])) 
				{
					NodeRecord temp = find(open, connectingNodes[i]);
					float tempCost = curr.costSoFar + curr.node->distTo(connectingNodes[i]);
					if (temp.costSoFar > tempCost)
					{
						open.deleteObject(temp);

						temp.fromNode = curr.node;
						temp.costSoFar = tempCost;
						temp.estimatedTotalCost = temp.costSoFar + heuristic.estimate(curr.node);

						open.insert(temp);
					}
				}
				else if (contains(closed, connectingNodes[i]))
				{
					NodeRecord temp = find(closed, connectingNodes[i]);
					float tempCost = curr.costSoFar + curr.node->distTo(connectingNodes[i]);
					if (temp.costSoFar > tempCost)
					{
						remove(closed,temp);

						temp.fromNode = curr.node;
						temp.costSoFar = tempCost;
						temp.estimatedTotalCost = temp.costSoFar + heuristic.estimate(curr.node);

						closed.push_back(temp);
					}
				}
				else
				{
					NodeRecord toAdd;
					toAdd.node = connectingNodes[i];
					toAdd.fromNode = curr.node;
					toAdd.costSoFar = curr.costSoFar + curr.node->distTo(toAdd.node);
					toAdd.estimatedTotalCost = toAdd.costSoFar + heuristic.estimate(toAdd.node);
					
					open.insert(toAdd);
				}
			}
		}
		return &vector<Node*>();
	}

	bool contains(PriorityQueue<NodeRecord>& pq, Node* node)
	{
		int size = pq.size();
		for (int i = 0; i < size; ++i)
		{
			if (node == pq.getIndex(i).node)
			{
				return true;
			}
		}
		return false;
	}

	bool contains(vector<NodeRecord>& closed, Node* node)
	{
		int size = closed.size();
		for (int i = 0; i < size; ++i)
		{
			if (node == closed[i].node)
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
			NodeRecord temp = pq.getIndex(i);
			if (toFind == temp.node)
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
		int size = closed.size();
		for (int i = 0; i < size; ++i)
		{
			NodeRecord temp = closed[i];
			if (toFind == temp.node)
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

