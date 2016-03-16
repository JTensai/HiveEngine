#include "Node.h"

Node::Node():row(-1),col(-1)
{
	parent = nullptr;
}

Node::Node(int row,int col):row(row),col(col)
{
	parent = nullptr;
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

void Node::setParent(Node* parent)
{
	this->parent = parent;
}

Node* Node::getParent()
{
	return parent;
}