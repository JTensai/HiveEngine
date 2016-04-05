#pragma once


#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#include "ParticleSystemData.h"
#include "Particle.h"
#include "Model.h"
#include "pSysModule.h"

namespace Hive {

	class ParticleEmitter
	{
	private:
		DParticleEmitter* data;
		std::vector<Particle> particles;
		std::vector<pSysModule*> modules;
		float time_between_particle_spawns;
		float time_since_last_spawn;
		float emitter_life;
		bool finished_emitting;
	public:
		ParticleEmitter();
		ParticleEmitter(DParticleEmitterHandle data_handle);
		void draw(glm::vec3 origin);
		void update(float delta);
		bool finished();
		~ParticleEmitter();
	};

}


