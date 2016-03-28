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
	int map_width;
	int map_depth;

	map<int, vector<Node*> > connections;
	
public:
	Graph();
	Graph(vector<char>&,int,int);
	~Graph();
	// Returns an array of connections(of class
	// Connection) outgoing from the given node
	vector<Node*>* get_connections(Node* fromNode);
	int get_map_width();
	int get_map_depth();
};

