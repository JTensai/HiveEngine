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
};

