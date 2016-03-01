#include "Graph.h"

Graph::Graph()
{
	Graph(tempMap);
}

template <size_t size_x, size_t size_y>
Graph::Graph(char (&map)[size_x][size_y]):row(size_x),col(size_y)
{
	connections = new Connections[size_x * size_ y][9];
	Node nodeMap[size_x][size_y];

	//create map of Nodes
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			nodeMap[i][j] = Node(i, j);
		}
	}

	//For each node create a list of Connections
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int numConnections = 0;
			Node currNode = nodeMap[i][j];
			if (i - 1 >= 0 && map[i - 1][j] == '1')
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i - 1][j]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			if (i + 1 < row && map[i + 1][j] == '1')
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i + 1][j]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			if (j - 1 >= 0 && map[i][j - 1] == '1')
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i][j - 1]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			if (j + 1 < col && map[i][j + 1] == '1')
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i][j + 1]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			if (i - 1 >= 0 && j - 1 >= 0 
				&& map[i - 1][j - 1] == '1' && (map[i - 1][j] == '1' || map[i][j - 1] == '1'))
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i - 1][j - 1]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			if (i - 1 >= 0 && j + 1 < col 
				&& map[i - 1][j + 1] == '1' && (map[i - 1][j] == '1' || map[i][j + 1] == '1'))
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i - 1][j + 1]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			if (i + 1 < row && j - 1 >= 0 
				&& map[i + 1][j - 1] == '1' && (map[i + 1][j] == '1' || map[i][j - 1] == '1'))
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i + 1][j - 1]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			if (i + 1 < row && j + 1 < col 
				&& map[i + 1][j + 1] == '1' && (map[i + 1][j] == '1' || map[i][j + 1] == '1'))
			{
				++numConnections;
				Connection* toAdd = new Connection(&currNode, &nodeMap[i + 1][j + 1]);
				connections[(i * col) + j][numConnections] = toAdd;
			}
			connections
		}
	}
}

Graph::~Graph()
{
	delete[] connections;
}

Node* Graph::getConnections(Node* fromNode)
{
	Node* listOfConnections = new Node[9];
	return listOfConnections;
}