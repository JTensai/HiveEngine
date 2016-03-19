#pragma once

#include "Node.h"

class BaseHeuristic
{
private:
	Node* goalNode;
public:
	BaseHeuristic(Node* goal):goalNode(goal) {}
	virtual ~BaseHeuristic() { delete goalNode; }
	Node* get_goal_node() { return goalNode; }
	virtual float estimate(Node* node) { return 0; }
};

