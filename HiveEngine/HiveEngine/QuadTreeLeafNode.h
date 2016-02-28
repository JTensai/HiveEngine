#pragma once
#include "QuadTreeNode.h"

#include <glm\glm.hpp>

class QuadTreeLeafNode :
	public QuadTreeNode
{
public:
	QuadTreeLeafNode();
	glm::vec2 get_contained_point();
	bool get_is_empty();
	void insert(glm::vec2 point);
	~QuadTreeLeafNode();

private:
	//Unit data perhaps? :
	//Unit contained
	////{glm::vec2 Unit.position,
	//// float Unit.radius}
	glm::vec2 contained_point;
	bool is_empty;
};

