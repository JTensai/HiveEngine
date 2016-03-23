#pragma once

#include "Node.h"
#include "Math.h"

class Connection
{
private:
	int cost;
	Node* from_node;
	Node* to_node;
public:
	Connection(Node* from_node, Node* to_node);
	~Connection();
	int get_cost();
	Node* get_from_node();
	Node* get_to_node();
};