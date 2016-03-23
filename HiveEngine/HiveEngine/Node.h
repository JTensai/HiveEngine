#pragma once

#include <math.h>

class Node
{
private:
	int row;
	int col;
	Node* parent;
public:
	Node();
	Node(int,int);
	~Node();
	int get_row();
	int get_col();
	float distance_to(Node* toNode);
	void set_parent(Node* parent);
	Node* get_parent();

	bool operator!=(const Node &other) const { return row != other.row || col != other.col; }
	bool operator==(const Node &other) const { return row == other.row && col == other.col; }
};

