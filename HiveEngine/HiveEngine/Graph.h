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
	Graph(char(&map)[size_x][size_y]):numRows(size_x), numCols(size_y)
	{
		//connections = new Connections[size_x * size_ y][9];
		Node* nodeMap[size_x][size_y];

		//create map of Nodes
		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < numCols; ++j)
			{
				nodeMap[i][j] = new Node(i, j);
			}
		}

		//For each node create a list of Connections
		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < numCols; ++j)
			{
				Node* currNode = nodeMap[i][j];
				int key = (i * numCols) + j;
				connections[key] = vector<Node*>();
				if (i - 1 >= 0 && map[i - 1][j] == '1')
				{
					connections[key].push_back(nodeMap[i - 1][j]);
				}
				if (i + 1 < numRows && map[i + 1][j] == '1')
				{
					connections[key].push_back(nodeMap[i + 1][j]);
				}
				if (j - 1 >= 0 && map[i][j - 1] == '1')
				{
					connections[key].push_back(nodeMap[i][j - 1]);
				}
				if (j + 1 < numCols && map[i][j + 1] == '1')
				{
					connections[key].push_back(nodeMap[i][j + 1]);
				}
			}
		}
	}
	~Graph();
	// Returns an array of connections(of class
	// Connection) outgoing from the given node
	vector<Node*>* getConnections(Node* fromNode);

	//This structure is used to keep track of the information we need for each node
	struct NodeRecord
	{
		Node* node;
		NodeRecord* fromNode;
		float costSoFar;
		float estimatedTotalCost;
		bool operator!=(const NodeRecord &other) const { return *node != *other.node; }
		bool operator==(const NodeRecord &other) const { return *node == *other.node; }
		bool operator<(const NodeRecord &other) const { return estimatedTotalCost < other.estimatedTotalCost; }
		bool operator>(const NodeRecord &other) const { return estimatedTotalCost > other.estimatedTotalCost; }
	};

	vector<Node*>* pathfindAStar(Graph graph, Node* start, Node* end, BaseHeuristic* heuristic)
	{
		PriorityQueue<NodeRecord> open(graph.numRows * graph.numCols);
		vector<NodeRecord> closed;

		NodeRecord startRecord;
		startRecord.node = start;
		startRecord.fromNode = nullptr;
		startRecord.costSoFar = 0;
		startRecord.estimatedTotalCost = heuristic->estimate(start);

		open.insert(startRecord);

		while (open.size() > 0)
		{
			NodeRecord curr = open.deleteMin();
			closed.push_back(curr);

			if (*curr.node == *end)
			{
				return generatePath(curr,start);
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

						temp.fromNode = &curr;
						temp.costSoFar = tempCost;
						temp.estimatedTotalCost = temp.costSoFar + heuristic->estimate(curr.node);

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

						temp.fromNode = &curr;
						temp.costSoFar = tempCost;
						temp.estimatedTotalCost = temp.costSoFar + heuristic->estimate(curr.node);

						closed.push_back(temp);
					}
				}
				else
				{
					NodeRecord toAdd;
					toAdd.node = connectingNodes[i];
					toAdd.fromNode = &curr;
					toAdd.costSoFar = curr.costSoFar + curr.node->distTo(toAdd.node);
					toAdd.estimatedTotalCost = toAdd.costSoFar + heuristic->estimate(toAdd.node);
					
					open.insert(toAdd);
				}
			}
		}
		return &vector<Node*>();
	}

	vector<Node*>* generatePath(NodeRecord &curr, Node* start)
	{
		vector<Node*> path;
		path.insert(path.begin(), curr.node);

		while (*curr.node != *start)
		{
			curr = *curr.fromNode;
			path.insert(path.begin(),curr.node);
		}

		return &path;
	}

	bool contains(PriorityQueue<NodeRecord>& pq, Node* node)
	{
		int size = pq.size();
		for (int i = 0; i < size; ++i)
		{
			if (*node == *pq.getIndex(i).node)
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
			NodeRecord temp = pq.getIndex(i);
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

