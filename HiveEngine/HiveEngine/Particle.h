#pragma once

#include <glm\glm.hpp>

class Particle
{
public:
	Particle();
	~Particle();
	glm::vec4 color;
	float rotation;
	glm::vec3 position;
	float scale;
	float life;
	float lifeExpectancy;
};

