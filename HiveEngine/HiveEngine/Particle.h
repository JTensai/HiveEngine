#pragma once

#include <glm\glm.hpp>
#include <random>

#include "ParticleSystemData.h"

using namespace Hive;

class Particle
{
public:
	Particle();
	Particle(DParticleEmitter* data);
	~Particle();
	glm::vec4 color;
	float rotation;
	glm::vec3 position;
	glm::vec3 scale;
	float life;
	float lifeExpectancy;
};

