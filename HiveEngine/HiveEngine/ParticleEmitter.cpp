#include "ParticleEmitter.h"

using namespace Hive;

ParticleEmitter::ParticleEmitter()
{
}

ParticleEmitter::ParticleEmitter(DParticleEmitterHandle data_handle)
{
	data = DParticleEmitter::getItem(data_handle);
	time_between_particle_spawns = 1.0f / data->constantRate;
	time_since_last_spawn = 0.0f;
	// Spawn burst particles
	for (unsigned int i = 0; i < data->burst; i++)
	{
		particles.push_back(Particle(data));
	}
}

void ParticleEmitter::update(float delta)
{
	// Spawn new particles
	time_since_last_spawn += delta;
	while (time_since_last_spawn > time_between_particle_spawns)
	{
		particles.push_back(Particle(data));
		time_since_last_spawn -= time_between_particle_spawns;
	}

	for (unsigned int i = 0; i < particles.size(); i++)
	{
		// Update particle life
		particles[i].life += delta;

		// Update particle positions
		particles[i].position += (data->initialVelocity * delta);

		// Update particle scales

		// Update particle rotation

		// Update particle color

		// Kill dead particles
		if (particles[i].life >= particles[i].lifeExpectancy)
		{
			particles.erase(particles.begin()+i);
		}
	}
}

void ParticleEmitter::draw(glm::vec3 origin)
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		glm::mat4 world_transform = glm::translate(origin);
		world_transform *= glm::translate(particles.at(i).position);
		world_transform *= glm::scale(particles.at(i).scale);
		ServiceLocator::get_graphics()->queue_draw(DrawShader::ALPHA, world_transform, DModel::getIndex("QUAD_MODEL"), data->mat_handle);
	}
}

ParticleEmitter::~ParticleEmitter()
{
}
