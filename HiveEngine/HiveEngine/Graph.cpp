#include "Graph.h"

Graph::Graph()
{
	//Graph(tempMap);
}

Graph::~Graph()
{
	int size = num_rows * num_cols;
	for (int key = 0; key < size; ++key)
	{
		int tempSize = (int)connections[key].size();
		for (int i = 0; i < tempSize; ++i)
		{
			delete connections[key][i];
		}
		connections[key].clear();
	}
	connections.clear();
}

vector<Node*>* Graph::get_connections(Node* fromNode)
{
	int key = (fromNode->get_row() * num_cols) + fromNode->get_col();
	return &connections[key];
}