#include "Graph.h"
#include <iostream>

Graph::Graph()
{
	//Graph(tempMap);
}

Graph::Graph(vector<char>& char_map, int map_width, int map_depth):map_width(map_width),map_depth(map_depth)
{
	vector<Node*> node_map(char_map.size());
	for (int i = 0; i < map_width; ++i)
	{
		for (int j = 0; j < map_depth; ++j)
		{
			node_map[(i * map_depth) + j] = new Node(i, j);
		}
	}

	//For each node create a list of Connections
	for (int i = 0; i < map_width; ++i)
	{
		for (int j = 0; j < map_depth; ++j)
		{
			int key = (i * map_depth) + j;
			Node* curr_node = node_map[key];
			connections[key] = vector<Node*>();
			int temp_index = ((i - 1) * map_depth) + j;

			// 1 is walkable
			if (i - 1 >= 0 && char_map[temp_index] == '\x1')
			{
				connections[key].push_back(node_map[temp_index]);
			}
			temp_index = ((i + 1) * map_depth) + j;
			if (i + 1 < map_width && char_map[temp_index] == '\x1')
			{
				connections[key].push_back(node_map[temp_index]);
			}
			temp_index = key - 1;
			if (j - 1 >= 0 && char_map[temp_index] == '\x1')
			{
				connections[key].push_back(node_map[temp_index]);
			}
			temp_index = key + 1;
			if (j + 1 < map_depth && char_map[temp_index] == '\x1')
			{
				connections[key].push_back(node_map[temp_index]);
			}
		}
	}
}

Graph::~Graph()
{
	int size = map_width * map_depth;
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
	int key = (fromNode->get_width() * map_depth) + fromNode->get_depth();
	return &connections[key];
}