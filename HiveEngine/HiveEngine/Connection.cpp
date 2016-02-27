#include "Connection.h"



Connection::Connection(Node* fromNode, Node* toNode):fromNode(fromNode), toNode(toNode), cost(fromNode->distTo(toNode))
{
}


Connection::~Connection()
{
	delete fromNode;
	delete toNode;
}

int Connection::getCost() 
{ 
	return cost; 
}

Node* Connection::getFromNode() 
{
	return fromNode;
}

Node* Connection::getToNode()
{ 
	return toNode; 
}