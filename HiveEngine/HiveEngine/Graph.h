#pragma once

#include <math.h>
#include "Node.h"
#include "Connection.h"
#include <map>
#include <vector>

using namespace std;

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
};

