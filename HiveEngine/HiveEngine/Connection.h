#pragma once

#include "Node.h"
#include "Math.h"

class Connection
{
private:
	int cost;
	Node* fromNode;
	Node* toNode;
public:
	Connection(Node* fromNode, Node* toNode);
	~Connection();
	int getCost();
	Node* getFromNode();
	Node* getToNode();
};