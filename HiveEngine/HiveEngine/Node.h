#pragma once

#include <math.h>

class Node
{
private:
	int width;
	int depth;
	Node* parent;
public:
	Node();
	Node(int,int);
	~Node();
	int get_width();
	int get_depth();
	void set_width(int width);
	void set_depth(int depth);
	float distance_to(Node* toNode);
	void set_parent(Node* parent);
	Node* get_parent();

	bool operator!=(const Node &other) const { return width != other.width || depth != other.depth; }
	bool operator==(const Node &other) const { return width == other.width && depth == other.depth; }
};

