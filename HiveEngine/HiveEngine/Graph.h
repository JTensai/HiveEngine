#pragma once

#include <math.h>
#include "Node.h"
#include "Connection.h"

class Graph
{
private:
	// 1 is walkable
	char tempMap[8][8] =
	{
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1' }
	};
	int row;
	int col;
	template <size_t size_x, size_t size_y>
	Connection* connections[size_x][size_y][9];
	
public:
	Graph();
	template <size_t size_x, size_t size_y>
	Graph(char(&map)[size_x][size_y]);
	~Graph();
	// Returns an array of connections(of class
	// Connection) outgoing from the given node
	Node* getConnections(Node* fromNode);
};

