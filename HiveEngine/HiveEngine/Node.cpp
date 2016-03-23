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

int Node::get_row()
{
	return row;
}

int Node::get_col()
{
	return col;
}

float Node::distance_to(Node* toNode)
{
	int xDiff = toNode->get_row() - row;
	int yDiff = toNode->get_col() - col;
	return (float) sqrt(xDiff * xDiff + yDiff * yDiff);
}

void Node::set_parent(Node* parent)
{
	this->parent = parent;
}

Node* Node::get_parent()
{
	return parent;
}