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
	emitter_life = 0.0f;
	finished_emitting = false;

	// Create Modules
	for (int module_handle : data->modules_handles)
	{
		DModule* data = DModule::getItem(module_handle);
	}

	// Spawn burst particles
	for (unsigned int i = 0; i < data->burst; i++)
	{
		particles.push_back(Particle(data));
	}
}

void ParticleEmitter::update(float delta)
{
	if (finished_emitting)
		return;
	//Check if emitter should die
	emitter_life += delta;
	if (emitter_life >= data->emitterDuration && !data->looping)
	{
		finished_emitting = true;
	}

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
		DModelHandle handle = DModel::getIndex("GOBLIN_MODEL");
		handle = DModel::getIndex("QUAD_MODEL");
		DModel* thing = DModel::getItem(handle);
		const Model* model = thing->getAsset();
		for (int i = 0; i < model->get_num_meshes(); i++)
		{
			ServiceLocator::get_graphics()->queue_draw(DrawShader::ALPHA, world_transform, model->get_mesh(i), data->mat_handle);
		}
		
	}
}

bool ParticleEmitter::finished()
{
	return finished_emitting;
}

ParticleEmitter::~ParticleEmitter()
{
}
