#pragma once
#include "BaseHeuristic.h"
class EuclideanHeuristic :
	public BaseHeuristic
{
public:
	EuclideanHeuristic(Node* goal);
	virtual ~EuclideanHeuristic();
	float estimate(Node* node);
};

