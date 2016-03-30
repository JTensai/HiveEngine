#include "Graph.h"
#include <iostream>

Graph::Graph()
{
	//Graph(tempMap);
}

Graph::Graph(vector<char>& char_map, int map_width, int map_depth):map_width(map_width),map_depth(map_depth)
{
	vector<Node*> node_map(char_map.size());
	for (int i = 0; i < map_depth; ++i)
	{
		for (int j = 0; j < map_width; ++j)
		{
			node_map[(i * map_width) + j] = new Node(j, i);
		}
	}

	//For each node create a list of Connections
	for (int i = 0; i < map_depth; ++i)
	{
		for (int j = 0; j < map_width; ++j)
		{
			int key = (i * map_width) + j;
			Node* curr_node = node_map[key];
			connections[key] = vector<Node*>();
			int temp_index = ((i - 1) * map_width) + j;

			// 1 is walkable
			if (i - 1 >= 0 && char_map[temp_index] == '\x1')
			{
				connections[key].push_back(node_map[temp_index]);
			}
			temp_index = ((i + 1) * map_width) + j;
			if (i + 1 < map_depth && char_map[temp_index] == '\x1')
			{
				connections[key].push_back(node_map[temp_index]);
			}
			temp_index = key - 1;
			if (j - 1 >= 0 && char_map[temp_index] == '\x1')
			{
				connections[key].push_back(node_map[temp_index]);
			}
			temp_index = key + 1;
			if (j + 1 < map_width && char_map[temp_index] == '\x1')
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
	int key = (fromNode->get_depth() * map_width) + fromNode->get_width();
	return &connections[key];
}

int Graph::get_map_width()
{
	return map_width;
}

int Graph::get_map_depth()
{
	return map_depth;
}