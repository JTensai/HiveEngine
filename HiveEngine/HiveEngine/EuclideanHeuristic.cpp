#include "EuclideanHeuristic.h"

EuclideanHeuristic::EuclideanHeuristic(Node* goal) : BaseHeuristic(goal)
{
}

EuclideanHeuristic::~EuclideanHeuristic()
{
}

float EuclideanHeuristic::estimate(Node* node)
{
	return node->distTo(getGoalNode());
}