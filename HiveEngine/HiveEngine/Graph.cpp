#include "Graph.h"

Graph::Graph()
{
	Graph(tempMap);
}

template <size_t size_x, size_t size_y>
Graph::Graph(char (&map)[size_x][size_y]):row(size_x),col(size_y)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int numConnections = 0;
			Node* currNode = new Node(i,j);
			if (i - 1 >= 0 && map[i - 1][j] == '1')
			{
				++numConnections;
				Connection* toAdd = new Connection();
			}
		}
	}
}

Graph::~Graph()
{
}

Node* Graph::getConnections(Node* fromNode)
{
	Node* listOfConnections = new Node[9];
	return listOfConnections;
}