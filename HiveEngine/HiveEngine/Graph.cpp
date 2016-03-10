#include "Graph.h"

Graph::Graph()
{
	//Graph(tempMap);
}

template <size_t size_x, size_t size_y>
Graph::Graph(char (&map)[size_x][size_y]):row(size_x),col(size_y)
{
	//connections = new Connections[size_x * size_ y][9];
	Node* nodeMap[size_x][size_y];

	//create map of Nodes
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			nodeMap[i][j] = new Node(i, j);
		}
	}

	//For each node create a list of Connections
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			Node currNode = nodeMap[i][j];
			int key = (i * col) + j;
			map[key] = vector<Node*>();
			if (i - 1 >= 0 && map[i - 1][j] == '1')
			{
				map[key].push_back(map[i - 1][j]);
			}
			if (i + 1 < row && map[i + 1][j] == '1')
			{
				map[key].push_back(map[i + 1][j]);
			}
			if (j - 1 >= 0 && map[i][j - 1] == '1')
			{
				map[key].push_back(map[i][j - 1]);
			}
			if (j + 1 < col && map[i][j + 1] == '1')
			{
				map[key].push_back(map[i][j + 1]);
			}
			if (i - 1 >= 0 && j - 1 >= 0 
				&& map[i - 1][j - 1] == '1' && (map[i - 1][j] == '1' || map[i][j - 1] == '1'))
			{
				map[key].push_back(map[i - 1][j - 1]);
			}
			if (i - 1 >= 0 && j + 1 < col 
				&& map[i - 1][j + 1] == '1' && (map[i - 1][j] == '1' || map[i][j + 1] == '1'))
			{
				map[key].push_back(map[i - 1][j + 1]);
			}
			if (i + 1 < row && j - 1 >= 0 
				&& map[i + 1][j - 1] == '1' && (map[i + 1][j] == '1' || map[i][j - 1] == '1'))
			{
				map[key].push_back(map[i + 1][j - 1]);
			}
			if (i + 1 < row && j + 1 < col 
				&& map[i + 1][j + 1] == '1' && (map[i + 1][j] == '1' || map[i][j + 1] == '1'))
			{
				map[key].push_back(map[i + 1][j + 1]);
			}
		}
	}
}

Graph::~Graph()
{
	int size = row * col;
	for (int key = 0; key < size; ++key)
	{
		int tempSize = connections[key].size();
		for (int i = 0; i < tempSize; ++i)
		{
			delete connections[key][i];
		}
		connections[key].clear();
	}
	connections.clear();
}

vector<Node*>* Graph::getConnections(Node* fromNode)
{
	int key = (fromNode->getRow() * col) + fromNode->getCol();
	return &connections[key];
}