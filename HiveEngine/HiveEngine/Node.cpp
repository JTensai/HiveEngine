#include "Node.h"

Node::Node():row(-1),col(-1)
{
}

Node::Node(int row,int col):row(row),col(col)
{
}

Node::~Node()
{
}

int Node::getRow()
{
	return row;
}

int Node::getCol()
{
	return col;
}

float Node::distTo(Node* toNode)
{
	int xDiff = toNode->getRow() - row;
	int yDiff = toNode->getCol() - col;
	return (float) sqrt(xDiff * xDiff + yDiff * yDiff);
}