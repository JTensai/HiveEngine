#pragma once

#include <math.h>

class Node
{
private:
	int row;
	int col;
public:
	Node();
	Node(int,int);
	~Node();
	int getRow();
	int getCol();
	float distTo(Node* toNode);

	bool operator!=(const Node &other) const { return row != other.row || col != other.col; }
	bool operator==(const Node &other) const { return row == other.row && col == other.col; }
};

