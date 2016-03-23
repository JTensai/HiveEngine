#include "Node.h"

Node::Node():width(-1),depth(-1)
{
	parent = nullptr;
}

Node::Node(int width,int depth): width(width), depth(depth)
{
	parent = nullptr;
}

Node::~Node()
{
}

int Node::get_width()
{
	return width;
}

int Node::get_depth()
{
	return depth;
}

float Node::distance_to(Node* toNode)
{
	int xDiff = toNode->get_width() - width;
	int yDiff = toNode->get_depth() - depth;
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