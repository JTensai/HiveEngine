#include "ParticleSystemComponent.h"

using namespace Hive;

ParticleSystemComponent::ParticleSystemComponent()
{
}

void ParticleSystemComponent::update_component(float delta)
{
	//TODO: update component
	bool is_active = false;
	for (unsigned int i = 0; i < emitters.size(); i++)
	{
		if (emitters.at(i) == nullptr)
			continue;
		if (emitters.at(i)->finished())
		{
			delete emitters.at(i);
			emitters.at(i) = nullptr;
		}
		else
		{
			emitters.at(i)->update(delta);
			is_active = true;
		}
	}
	if (!is_active)
	{
		ParticleSystemComponent::destroy_component(self_handle);
	}
}

void ParticleSystemComponent::draw_component(const glm::mat4& VP)
{
	//TODO: draw component
	for (unsigned int i = 0; i < emitters.size(); i++)
	{
		if (emitters.at(i) == nullptr)
			continue;
		emitters.at(i)->draw(origin);
	}
}

void ParticleSystemComponent::load_from_data(ParticleSystemHandle self, DParticleSystemHandle data_handle, glm::vec3 origin)
{
	self_handle = self;
	ParticleSystemComponent::origin = origin;
	DParticleSystem* data = DParticleSystem::getItem(data_handle);

	for (unsigned int i = 0; i < data->emitters_handles.size(); i++)
	{
		emitters.push_back(new ParticleEmitter(data->emitters_handles[i]));
	}
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	for (ParticleEmitter* emitter : emitters)
	{
		if (emitter != nullptr)
			delete emitter;
	}
}