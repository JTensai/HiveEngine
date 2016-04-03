#include "Particle.h"



Particle::Particle()
{
	color = glm::vec4(1, 1, 1, 1);
	rotation = 0.0f;
	position = glm::vec3(0, 0, 0);
	scale = 1.0f;
	life = 0.0f;
	lifeExpectancy = 1.0f;
}


Particle::~Particle()
{
}
