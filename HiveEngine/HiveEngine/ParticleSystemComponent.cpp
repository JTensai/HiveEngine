#include "ParticleSystemComponent.h"

using namespace Hive;

ParticleSystemComponent::ParticleSystemComponent()
{
}

void ParticleSystemComponent::update_component(float delta)
{
	//TODO: update component
	for (unsigned int i = 0; i < emitters.size(); i++)
	{
		emitters.at(i).update(delta);
	}
}

void ParticleSystemComponent::draw_component(const glm::mat4& VP)
{
	//TODO: draw component
	for (unsigned int i = 0; i < emitters.size(); i++)
	{
		emitters.at(i).draw(origin);
	}
}

void ParticleSystemComponent::load_from_data(int data_handle, glm::vec3 origin)
{
	DParticleSystem* data = DParticleSystem::getItem(data_handle);
	origin = origin;

	for (unsigned int i = 0; i < data->emitters_handles.size(); i++)
	{
		emitters.push_back(ParticleEmitter(data->emitters_handles[i]));
	}
}

ParticleSystemComponent::~ParticleSystemComponent()
{
}