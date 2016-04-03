#pragma once


#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#include "ParticleSystemData.h"
#include "Particle.h"
#include "Model.h"

namespace Hive {

	class ParticleEmitter
	{
	private:
		DParticleEmitter* data;
		std::vector<Particle> particles;
		float time_between_particle_spawns;
		float time_since_last_spawn;
	public:
		ParticleEmitter();
		ParticleEmitter(int data_handle);
		void draw(glm::vec3 origin);
		void update(float delta);
		~ParticleEmitter();
	};

}


