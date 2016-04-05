#include "Particle.h"



float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

Particle::Particle()
{
	color = glm::vec4(1, 1, 1, 1);
	rotation = 0.0f;
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1.0f,1.0f,1.0f);
	life = 0.0f;
	lifeExpectancy = 1.0f;
}

Particle::Particle(DParticleEmitter* data) {
	color = glm::vec4(1, 1, 1, 1);
	rotation = 0.0f;
	position = glm::vec3(0, 0, 0);
	float randScale = RandomFloat(data->initialSize.x, data->initialSize.y);
	scale = glm::vec3(randScale, randScale, randScale);
	life = 0.0f;
	lifeExpectancy = RandomFloat(data->lifetime.x, data->lifetime.y);
}

Particle::~Particle()
{
}