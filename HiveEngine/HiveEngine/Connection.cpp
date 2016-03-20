#include "Connection.h"

Connection::Connection(Node* fromNode, Node* toNode):from_node(fromNode), to_node(toNode), cost(fromNode->distance_to(toNode))
{
}


Connection::~Connection()
{
	delete from_node;
	delete to_node;
}

int Connection::get_cost() 
{ 
	return cost; 
}

Node* Connection::get_from_node() 
{
	return from_node;
}

Node* Connection::get_to_node()
{ 
	return to_node;
}